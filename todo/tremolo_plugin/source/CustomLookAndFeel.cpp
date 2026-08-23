namespace tremolo {
CustomLookAndFeel::CustomLookAndFeel() {
  setColour(juce::PopupMenu::backgroundColourId, juce::Colour{0xff14ab7b});
  setColour(juce::PopupMenu::textColourId, juce::Colours::beige);
  setColour(juce::ComboBox::textColourId, juce::Colours::beige);
  setColour(juce::Label::textColourId, getColor(Colors::textColour));
}

juce::Colour CustomLookAndFeel::getColor(Colors colorName) {
  static const std::array colors{juce::Colour{0xFF008171},
                                 juce::Colour{0xFF008171},
                                 juce::Colour{0xFFf3ff00}};
  return colors.at(juce::toUnderlyingType(colorName));
}

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

    g.setColour(getColor(Colors::accentColour));
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

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                         int x,
                                         int y,
                                         int width,
                                         int height,
                                         float sliderPos,
                                         const float rotaryStartAngle,
                                         const float rotaryEndAngle,
                                         juce::Slider& slider) {
  auto bounds = juce::Rectangle{x, y, width, height}.toFloat().reduced(3.75f);
  g.setColour(juce::Colour{0xff0b4337});
  g.fillEllipse(bounds);

  juce::Path valueArc;

  auto radius = juce::jmin(width - 2, height - 2) / 2.0f;
  auto toAngle =
      rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
  auto lineW = juce::jmin(8.0f, radius * 0.5f);
  auto arcRadius = radius - lineW * 0.5f;

  valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius,
                         arcRadius, 0.0f, rotaryStartAngle, toAngle, true);

  g.setColour(getColor(Colors::accentColour));
  g.strokePath(valueArc, juce::PathStrokeType(4, juce::PathStrokeType::curved,
                                              juce::PathStrokeType::rounded));

  auto boundsInner = bounds.reduced(3.f);
  /* auto gradient = juce::ColourGradient::vertical(
      juce::Colour{0xFF189076}, juce::Colour{0xFF14ab7b}, boundsInner);
  gradient.addColour(0.73, juce::Colour{0xFF009b77});
  g.setGradientFill(gradient);
  g.fillEllipse(boundsInner);*/

  // boundsInner = boundsInner.reduced(1.25f);
  auto gradient = juce::ColourGradient::vertical(
      juce::Colour{0xFF008171}, juce::Colour{0xFF004d44}, boundsInner);
  g.setGradientFill(gradient);
  g.fillEllipse(boundsInner);

  boundsInner = boundsInner.reduced(5.75f);
  gradient = juce::ColourGradient::vertical(
      juce::Colour{0xFF14ab7b}, juce::Colour{0xFF189076}, boundsInner);
  gradient.addColour(0.73, juce::Colour{0xFF009b77});
  g.setGradientFill(gradient);
  g.setOpacity(0.7f);
  g.fillEllipse(boundsInner);

  // Gloss
  auto glossBounds = boundsInner;

  juce::ColourGradient gloss(juce::Colours::white.withAlpha(0.6f),
                             glossBounds.getX(), glossBounds.getY(),

                             juce::Colours::white.withAlpha(0.0f),
                             glossBounds.getX(), glossBounds.getCentreY() - 10,
                             false);

  g.setGradientFill(gloss);
  g.fillEllipse(glossBounds);

  // Gloss
  juce::ColourGradient shadow(
      juce::Colours::black.withAlpha(0.0f), boundsInner.getX(),
      boundsInner.getCentreY() + 10, juce::Colours::black.withAlpha(0.1f),
      boundsInner.getX(), boundsInner.getBottom(), false);

  g.setGradientFill(shadow);
  g.fillEllipse(boundsInner);
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
