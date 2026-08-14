#pragma once

namespace tremolo {
class RateSlider : public juce::Slider {
public:
  void paint(juce::Graphics& g) override {
    auto sliderPos = (float)valueToProportionOfLength(getValue());
    jassert(sliderPos >= 0 && sliderPos <= 1.0f);

    const auto rotaryParams = getRotaryParameters();
    const auto rotaryStartAngle = rotaryParams.startAngleRadians;
    const auto rotaryEndAngle = rotaryParams.endAngleRadians;

    auto outline = findColour(Slider::rotarySliderOutlineColourId);
    auto fill = findColour(Slider::rotarySliderFillColourId);

    auto bounds = getLocalBounds().toFloat().reduced(10);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle =
        rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;


    if (isEnabled()) {
      juce::Path valueArc;
      valueArc.addPieSegment(getLocalBounds().toFloat(), rotaryStartAngle,
                             toAngle, 0);

      g.setColour(juce::Colours::beige);
      g.fillPath(valueArc);
    }



  }
};
}  // namespace tremolo