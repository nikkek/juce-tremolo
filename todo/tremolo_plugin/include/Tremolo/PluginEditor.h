#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent logo;

  LfoVisualizer lfoVisualizer;

  RateSlider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::Slider depthSlider;
  juce::SliderParameterAttachment depthAttachment;

  juce::ToggleButton bypassButton{"BYPASSED"};
  juce::ButtonParameterAttachment bypassAttachment;

  // juce::Slider lfoCurveWidthSlider;

  CustomLookAndFeel lookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
