namespace tremolo {
class LfoVisualizer : public juce::Component,
                      private juce::AudioProcessorParameter::Listener {
public:
  enum class LfoWaveform : size_t {
    sine = 0,
    triangle = 1,
    square = 2,
  };

  ~LfoVisualizer() override {
    if (waveformParameter != nullptr)
      waveformParameter->removeListener(this);
  }

  void paint(juce::Graphics& g) override {
    g.setColour(juce::Colours::beige);
    g.strokePath(path(currentLfoWaveform), juce::PathStrokeType{strokeWidth});
  }

  void resized() override { updatePaths(strokeWidth); }

  void updatePaths(float strokeWidth) {
    for (auto& waveform : waveforms)
      waveform.clear();

    const auto halfHeight = getHeight() / 2.f;
    const auto amplitude = halfHeight - strokeWidth / 2.f;

    path(LfoWaveform::sine).startNewSubPath(0.f, halfHeight);

    path(LfoWaveform::triangle).startNewSubPath(0.f, halfHeight);

    path(LfoWaveform::square).startNewSubPath(0.f, halfHeight);

    for (const auto x : std::views::iota(-4, getWidth() + 4)) {
      const auto phase = 0.05f * x;

      path(LfoWaveform::sine).lineTo(x, halfHeight + amplitude * sine(phase));

      path(LfoWaveform::triangle)
          .lineTo(x, halfHeight + amplitude * triangle(phase));

      path(LfoWaveform::square)
          .lineTo(x, halfHeight + amplitude * square(phase));
    }
  }

  void setWaveform(LfoWaveform waveform) {
    currentLfoWaveform = waveform;
    repaint();
  }

  void setStrokeWidth(float widthValue) {
    strokeWidth = widthValue;
    updatePaths(strokeWidth);
    repaint();
  }

  void setParameter(juce::AudioParameterChoice& parameter) {
    waveformParameter = &parameter;
    parameter.addListener(this);

    setWaveform(static_cast<LfoWaveform>(parameter.getIndex()));
  }

  void parameterValueChanged(int parameterIndex, float newValue) override {
    juce::MessageManager::callAsync([this] {
      const auto waveformIndex = waveformParameter->getIndex();
      setWaveform(static_cast<LfoWaveform>(waveformIndex));
    });
  };

  void parameterGestureChanged(int parameterIndex,
                               bool gestureIsStarting) override {

  };

private:
  juce::AudioParameterChoice* waveformParameter = nullptr;

  static float sine(float phase) { return std::sin(phase); }

  static float triangle(float phase) {
    return (2.f / juce::MathConstants<float>::pi) * std::asin(std::sin(phase));
  }

  static float square(float phase) {
    return std::tanh(20.0f * std::sin(phase));
  }

  float strokeWidth = 4.f;

  std::array<juce::Path, 3> waveforms;

  LfoWaveform currentLfoWaveform = LfoWaveform::sine;

  juce::Path& path(LfoWaveform waveform) {
    return waveforms[static_cast<size_t>(waveform)];
  }
};

}  // namespace tremolo