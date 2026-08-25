namespace tremolo {

namespace {
void drawButtonInset(juce::Rectangle<float> bounds, juce::Graphics& g) {
  auto outlineGradient = juce::ColourGradient::vertical(
      juce::Colour{0xFF008171}, juce::Colour{0xFF004d44}, bounds);
  g.setGradientFill(outlineGradient);
  g.fillRoundedRectangle(bounds.toFloat(), 6.f);
}

void drawGreenGradientButton(const juce::Rectangle<float> bounds,
                             juce::Graphics& g) {
  auto buttonGradient = juce::ColourGradient::vertical(
      juce::Colour{0xFF14ab7b}, juce::Colour{0xFF189076}, bounds);

  buttonGradient.addColour(0.73, juce::Colour{0xFF009b77});
  g.setGradientFill(buttonGradient);
  g.fillRoundedRectangle(bounds.toFloat(), 4.f);
}
}  // namespace

CustomLookAndFeel::CustomLookAndFeel() {
  setColour(juce::PopupMenu::backgroundColourId, juce::Colour{0xff14ab7b});
  setColour(juce::PopupMenu::textColourId, juce::Colours::beige);
  setColour(juce::PopupMenu::highlightedBackgroundColourId,
            getColor(Colors::darkGreen));
  setColour(juce::PopupMenu::highlightedTextColourId,
            getColor(Colors::accentColour));
  setColour(juce::ComboBox::textColourId, juce::Colours::beige);
  setColour(juce::Label::textColourId, getColor(Colors::textColour));
}

juce::Colour CustomLookAndFeel::getColor(Colors colorName) {
  static const std::array colors{
      juce::Colour{0xFF008171}, juce::Colour{0xFF008171},
      juce::Colour{0xFFf3ff00}, juce::Colour{0xFF189076}};
  return colors.at(juce::toUnderlyingType(colorName));
}

void CustomLookAndFeel::drawToggleButton(juce::Graphics& g,
                                         juce::ToggleButton& button,
                                         bool shouldDrawButtonAsHighlighted,
                                         bool shouldDrawButtonAsDown) {
  const auto bounds = button.getLocalBounds().toFloat().reduced(2);

  const auto outlineBounds = button.getLocalBounds().toFloat();

  drawButtonInset(outlineBounds, g);

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

  // Shadow
  juce::ColourGradient shadow(
      juce::Colours::black.withAlpha(0.0f), boundsInner.getX(),
      boundsInner.getCentreY() + 10, juce::Colours::black.withAlpha(0.1f),
      boundsInner.getX(), boundsInner.getBottom(), false);

  g.setGradientFill(shadow);
  g.fillEllipse(boundsInner);
}

void CustomLookAndFeel::drawComboBox(juce::Graphics& g,
                                     int width,
                                     int height,
                                     bool,
                                     int,
                                     int,
                                     int,
                                     int,
                                     juce::ComboBox& box) {
  const auto bounds = box.getLocalBounds().toFloat();
  drawButtonInset(bounds, g);

  const auto buttonBounds = bounds.reduced(2);
  drawGreenGradientButton(buttonBounds, g);

  auto arrowBounds = buttonBounds.reduced(8, 9);
  arrowBounds.removeFromLeft(104);

  juce::Path arrow;
  arrow.startNewSubPath(arrowBounds.getTopLeft());
  arrow.lineTo(arrowBounds.getTopRight());
  arrow.lineTo(arrowBounds.getCentreX(), arrowBounds.getBottom());
  arrow.closeSubPath();

  g.setColour(juce::Colours::beige);
  g.fillPath(arrow);
}

void CustomLookAndFeel::positionComboBoxText(juce::ComboBox& box,
                                             juce::Label& labelToPosition) {
  auto bounds = box.getLocalBounds().reduced(10, 6);
  bounds.removeFromRight(12);
  labelToPosition.setBounds(bounds);
  labelToPosition.setJustificationType(juce::Justification::centred);
  labelToPosition.setFont(getComboBoxFont(box));
}

juce::PopupMenu::Options CustomLookAndFeel::getOptionsForComboBoxPopupMenu(
    juce::ComboBox& box,
    juce::Label& label) {
  auto bounds = box.getScreenBounds().reduced(2, 0);
  return LookAndFeel_V4::getOptionsForComboBoxPopupMenu(box, label)
      .withStandardItemHeight(24)
      .withMinimumWidth(128)
      .withItemThatMustBeVisible(0)
      .withTargetScreenArea(bounds);
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
