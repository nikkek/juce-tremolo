namespace tremolo {
class LfoVisualizer : public juce::Component {
public:
  void paint(juce::Graphics& g) override {
    g.setColour(juce::Colours::beige);
    g.strokePath(sine, juce::PathStrokeType{strokeWidth});
  }

  void resized() override {
    sine.clear();

    const auto halfHeight = getHeight() / 2;
    const auto amplitude = halfHeight - strokeWidth / 2;

    sine.startNewSubPath(0.f, halfHeight + amplitude * std::sin(0.f));
    for (const auto x : std::views::iota(-4, getWidth() + 4)) {
      sine.lineTo(x, halfHeight + amplitude * std::sin(0.05f * x));
    }
  }

private:
  const float strokeWidth = 4.f;
  juce::Path sine;
};

}  // namespace tremolo