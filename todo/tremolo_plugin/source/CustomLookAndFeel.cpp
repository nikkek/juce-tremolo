namespace tremolo {
void CustomLookAndFeel::drawToggleButton(juce::Graphics& g,
                                         juce::ToggleButton& button,
                                         bool shouldDrawButtonAsHighlighted,
                                         bool shouldDrawButtonAsDown) {
  const auto bounds = button.getLocalBounds().reduced(2);

  auto outlineBounds = button.getLocalBounds();
  auto outlineGradient = juce::ColourGradient::vertical(
      juce::Colour{0xFF008171}, juce::Colour{0xFF004d44}, outlineBounds);
  g.setGradientFill(outlineGradient);
  g.fillRoundedRectangle(outlineBounds.toFloat(), 6.f);

  if (button.getToggleState()) {
    auto buttonGradient = juce::ColourGradient::vertical(
        juce::Colour{0xFF189076}, juce::Colour{0xFF14ab7b}, bounds);

    buttonGradient.addColour(0.73, juce::Colour{0xFF009b77});

    g.setGradientFill(buttonGradient);

    if (shouldDrawButtonAsHighlighted) {
      g.setOpacity(0.7f);
    }
    g.fillRoundedRectangle(bounds.toFloat(), 4.f);

    g.setColour(accentColour);
  } else {
    auto buttonGradient = juce::ColourGradient::vertical(
        juce::Colour{0xFF14ab7b}, juce::Colour{0xFF189076}, bounds);

    buttonGradient.addColour(0.73, juce::Colour{0xFF009b77});
    g.setGradientFill(buttonGradient);

    if (shouldDrawButtonAsHighlighted) {
      g.setOpacity(0.7f);
    }
    g.fillRoundedRectangle(bounds.toFloat(), 4.f);

    g.setColour(juce::Colours::beige);
  }
  g.setFont(getComponentFonts());
  g.drawText(button.getButtonText(), bounds, juce::Justification::centred,
             false);
}

juce::FontOptions CustomLookAndFeel::geistRegular() {
  static const auto result = juce::Typeface::createSystemTypefaceFor(
      assets::GeistRegular_ttf, assets::GeistRegular_ttfSize);

  return juce::FontOptions{result};
}

juce::FontOptions CustomLookAndFeel::geistBold() {
  static const auto result = juce::Typeface::createSystemTypefaceFor(
      assets::GeistBold_ttf, assets::GeistBold_ttfSize);

  return juce::FontOptions{result};
}

}  // namespace tremolo
