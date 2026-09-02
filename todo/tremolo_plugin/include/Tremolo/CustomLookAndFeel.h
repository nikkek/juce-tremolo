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

  juce::ColourGradient makeGreenGradientInverted(
      juce::Rectangle<float> bounds) {
    auto gradient = juce::ColourGradient::vertical(
        juce::Colour{0xFF189076}, juce::Colour{0xFF14ab7b}, bounds);

    gradient.addColour(0.73, juce::Colour{0xFF009b77});

    return gradient;
  }

  juce::ColourGradient makeGreenGradient(juce::Rectangle<float> bounds) {
    auto gradient = juce::ColourGradient::vertical(
        juce::Colour{0xFF14ab7b}, juce::Colour{0xFF189076}, bounds);

    gradient.addColour(0.73, juce::Colour{0xFF009b77});

    return gradient;
  }

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

  void drawPopupMenuItem(juce::Graphics& g,
                         const juce::Rectangle<int>& area,
                         const bool isSeparator,
                         const bool isActive,
                         const bool isHighlighted,
                         const bool isTicked,
                         const bool hasSubMenu,
                         const juce::String& text,
                         const juce::String& shortcutKeyText,
                         const juce::Drawable* icon,
                         const juce::Colour* const textColourToUse) override;

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
