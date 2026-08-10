
namespace tremolo {
namespace {
auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {
  auto& parameterReference = *parameter;
  processor.addParameter(parameter.release());
  return parameterReference;
}

juce::AudioParameterFloat& createModulationRateParameter(
    juce::AudioProcessor& processor) {
  constexpr auto versionHint = 1;
  auto parameter = std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"modulation.rate", versionHint}, "Modulation rate",
      juce::NormalisableRange<float>{0.1f, 20.f, 0.01f, 0.4f}, 5.f,
      juce::AudioParameterFloatAttributes{}.withLabel("Hz"));
  return addParameterToProcessor(processor, std::move(parameter));
}

juce::AudioParameterFloat& createGainParameter(
    juce::AudioProcessor& processor) {
  constexpr auto versionHint = 1;
  auto parameter = std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"gain", versionHint}, "Gain",
      juce::NormalisableRange<float>{-12.f, 12.f, 0.1f}, 0.f,
      juce::AudioParameterFloatAttributes{}.withLabel("dB"));
  return addParameterToProcessor(processor, std::move(parameter));
}

juce::AudioParameterBool& createBypassParameter(
    juce::AudioProcessor& processor) {
  constexpr auto versionHint = 1;
  auto parameter = std::make_unique<juce::AudioParameterBool>(
      juce::ParameterID{"bypassed", versionHint}, "Bypass", false);
  return addParameterToProcessor(processor, std::move(parameter));
}

juce::AudioParameterChoice& createModulationWaveformParameter(
    juce::AudioProcessor& processor) {
  constexpr auto versionHint = 1;
  auto parameter = std::make_unique<juce::AudioParameterChoice>(
      juce::ParameterID{"modulation.waveform", versionHint},
      "Modulation waveform", juce::StringArray{"Sine", "Triangle", "Square"},
      0);
  return addParameterToProcessor(processor, std::move(parameter));
}

juce::AudioParameterFloat& createModulationDepthParameter(
    juce::AudioProcessor& processor) {
  constexpr auto versionHint = 1;
  auto parameter = std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"modulation.depth", versionHint}, "Modulation depth",
      juce::NormalisableRange<float>{0.f, 1.f, 0.01f}, 0.4f,
      juce::AudioParameterFloatAttributes{}.withLabel("%"));
  return addParameterToProcessor(processor, std::move(parameter));
}

}  // namespace

Parameters::Parameters(juce::AudioProcessor& processor)
    : rate{createModulationRateParameter(processor)},
      gain{createGainParameter(processor)},
      bypassed{createBypassParameter(processor)},
      waveform{createModulationWaveformParameter(processor)},
      depth{createModulationDepthParameter(processor)} {
  juce::ignoreUnused(processor);
}
}  // namespace tremolo
