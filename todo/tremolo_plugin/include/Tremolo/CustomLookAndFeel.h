#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
  void drawToggleButton(juce::Graphics&,
                        juce::ToggleButton&,
                        bool shouldDrawButtonAsHighlighted,
                        bool shouldDrawButtonAsDown) override;
  static juce::FontOptions getSideLabelFonts() {
    return geistRegular().withPointHeight(10.f);
  }

  juce::Colour textColour{0xFF008171};
  juce::Colour secondaryColour{};
  juce::Colour accentColour{0xFFf3ff00};

private:
  static juce::FontOptions geistRegular();
};

}  // namespace tremolo
