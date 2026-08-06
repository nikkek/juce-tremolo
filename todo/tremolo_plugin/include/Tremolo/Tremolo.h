#pragma once

namespace tremolo {
class Tremolo {
public:
  enum class LfoWaveform : size_t {
    sine = 0,
    triangle = 1,
    square = 2,
  };

  Tremolo() {
    for (auto& lfo : lfos) {
      lfo.setFrequency(5.f, true);
    }
  }
  void prepare(double sampleRate, int expectedMaxFramesPerBlock) {
    const juce::dsp::ProcessSpec processSpec{
        .sampleRate = sampleRate,
        .maximumBlockSize =
            static_cast<juce::uint32>(expectedMaxFramesPerBlock),
        .numChannels = 1u,
    };

    for (auto& lfo : lfos) {
      lfo.prepare(processSpec);
    }

    transitionDurationSamples = sampleRate * transitionDurationMs / 1000.f;
  }

  void setLfoWaveform(LfoWaveform waveform) {
    jassert(waveform == LfoWaveform::sine ||
            waveform == LfoWaveform::triangle ||
            waveform == LfoWaveform::square);

    lfoToSet = waveform;
  }

  void setModulationRate(float rateHz) {
    for (auto& lfo : lfos) {
      lfo.setFrequency(rateHz);
    }
  }

  void process(juce::AudioBuffer<float>& buffer) noexcept {
    updateLfoWaveform();

    // for each frame
    for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {
      // generate the LFO value
      const auto lfoValue = getNextLfoValue();

      // calculate the modulation value
      constexpr auto modulationDepth = 0.4f;
      const auto modulationValue =
          (1.0f - modulationDepth) + modulationDepth * (lfoValue + 1.0f) * 0.5f;

      // for each channel sample in the frame
      for (const auto channelIndex :
           std::views::iota(0, buffer.getNumChannels())) {
        // get the input sample
        const auto inputSample = buffer.getSample(channelIndex, frameIndex);

        // modulate the sample
        const auto outputSample = inputSample * modulationValue;

        // set the output sample
        buffer.setSample(channelIndex, frameIndex, outputSample);
      }
    }
  }

  void reset() noexcept {
    for (auto& lfo : lfos) {
      lfo.reset();
    }
  }

private:
  // You should put class members and private functions here

  static float triangle(float phase) {
    // const auto ft = phase / juce::MathConstants<float>::twoPi;
    // return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
    return std::abs(2 * phase / juce::MathConstants<float>::pi) - 1.f;
  }

  static float square(float phase) {
    return std::tanh(20.0f * std::sin(phase));
  }

  float getNextLfoValue() {
    if (isTransitioning) {
      if (transitionProgress <= 1.f) {
        currentLfoValue =
            lfos[juce::toUnderlyingType(currentLfo)].processSample(0.f);
        targetLfoValue =
            lfos[juce::toUnderlyingType(lfoToSet)].processSample(0.f);

        transitionedLfoValue =
            (targetLfoValue - currentLfoValue) * transitionProgress +
            currentLfoValue;

        transitionProgress += 1.f / transitionDurationSamples;
        return transitionedLfoValue;
      } else {
        transitionProgress = 0.f;
        isTransitioning = false;
        currentLfo = lfoToSet;
        return lfos[juce::toUnderlyingType(currentLfo)].processSample(0.f);
      }
    } else {
      return lfos[juce::toUnderlyingType(currentLfo)].processSample(0.f);
    }
  }

  void updateLfoWaveform() {
    if (currentLfo != lfoToSet && !isTransitioning) {
      isTransitioning = true;
      transitionProgress = 0.f;
    }
  }

  std::array<juce::dsp::Oscillator<float>, 3u> lfos{
      juce::dsp::Oscillator<float>{[](auto phase) { return std::sin(phase); }},
      juce::dsp::Oscillator<float>{triangle},
      juce::dsp::Oscillator<float>{square},
  };

  LfoWaveform currentLfo = LfoWaveform::sine;
  LfoWaveform lfoToSet = currentLfo;
  float currentLfoValue;
  float targetLfoValue;
  float transitionedLfoValue;
  float transitionProgress = 0.f;
  float transitionDurationMs = 50.f;
  float transitionDurationSamples = 1000.f;
  bool isTransitioning = false;
};
}  // namespace tremolo