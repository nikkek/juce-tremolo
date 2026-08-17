namespace tremolo {
void CustomLookAndFeel::drawToggleButton(juce::Graphics& g,
                                         juce::ToggleButton& button,
                                         bool shouldDrawButtonAsHighlighted,
                                         bool shouldDrawButtonAsDown) {
  const auto bounds = button.getLocalBounds().reduced(2);

  if (button.getToggleState()) {
    auto buttonGradient = juce::ColourGradient::vertical(
        juce::Colour{0xFF189076}, juce::Colour{0xFF14ab7b}, bounds);

    buttonGradient.addColour(0.73, juce::Colour{0xFF009b77});
    g.setGradientFill(buttonGradient);

    g.fillRoundedRectangle(bounds.toFloat(), 4.f);

    g.setColour(juce::Colour{0xFFf3ff00});
  } else {
    auto buttonGradient = juce::ColourGradient::vertical(
        juce::Colour{0xFF14ab7b}, juce::Colour{0xFF189076}, bounds);

    buttonGradient.addColour(0.73, juce::Colour{0xFF009b77});
    g.setGradientFill(buttonGradient);

    g.fillRoundedRectangle(bounds.toFloat(), 4.f);

    g.setColour(juce::Colours::beige);
  }
  g.drawText(button.getButtonText(), bounds, juce::Justification::centred,
             false);
}
}  // namespace tremolo
