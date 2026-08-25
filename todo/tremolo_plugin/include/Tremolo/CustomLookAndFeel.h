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

  void drawComboBox(juce::Graphics& g,
                    int width,
                    int height,
                    bool,
                    int,
                    int,
                    int,
                    int,
                    juce::ComboBox& box) override;

  juce::Font getComboBoxFont(juce::ComboBox&) override {
    return geistBold().withPointHeight(12.f);
  }

  juce::Font getPopupMenuFont() override {
    return geistRegular().withPointHeight(12.f);
  }

  juce::Path getTickShape(float height) override { return {}; }

  void positionComboBoxText(juce::ComboBox&,
                            juce::Label& labelToPosition) override;

  juce::PopupMenu::Options getOptionsForComboBoxPopupMenu(
      juce::ComboBox&,
      juce::Label&) override;

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
