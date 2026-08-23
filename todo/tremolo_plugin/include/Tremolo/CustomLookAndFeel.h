#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
  CustomLookAndFeel();

  enum class Colors : size_t {
    textColour,
    secondaryColour,
    accentColour,
    darkGreen
  };

  static juce::Colour getColor(Colors colorName);

  void drawToggleButton(juce::Graphics&,
                        juce::ToggleButton&,
                        bool shouldDrawButtonAsHighlighted,
                        bool shouldDrawButtonAsDown) override;

  void drawRotarySlider(juce::Graphics& g,
                        int x,
                        int y,
                        int width,
                        int height,
                        float sliderPos,
                        const float rotaryStartAngle,
                        const float rotaryEndAngle,
                        juce::Slider& slider) override;

  static juce::FontOptions getSideLabelFonts() {
    return geistRegular().withPointHeight(10.f);
  }

  static juce::FontOptions getComponentFonts() {
    return geistBold().withPointHeight(12.f);
  }

private:
  static juce::FontOptions geistRegular();
  static juce::FontOptions geistBold();
};

}  // namespace tremolo
