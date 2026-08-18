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

  juce::ComboBox waveformComboBox;
  juce::ComboBoxParameterAttachment waveformAttachment;

  juce::ComboBox lookAndFeelComboBox;

  // juce::Slider lfoCurveWidthSlider;

  CustomLookAndFeel lookAndFeel;
  juce::LookAndFeel_V2 lookAndFeel_V2;
  juce::LookAndFeel_V3 lookAndFeel_V3;
  juce::LookAndFeel_V4 lookAndFeel_V4;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
