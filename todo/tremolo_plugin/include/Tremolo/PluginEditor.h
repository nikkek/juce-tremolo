#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent logo;

  LfoVisualizer lfoVisualizer;

  RateSlider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::Slider depthSlider;
  juce::SliderParameterAttachment depthAttachment;

  juce::Slider depthSlider2;
  juce::SliderParameterAttachment depthAttachment2;

  juce::ToggleButton bypassButton{"BYPASSED"};
  juce::ButtonParameterAttachment bypassAttachment;

  juce::Slider lfoCurveWidthSlider;

  juce::ImageComponent logoCenter;
  juce::ImageComponent logoRight;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
