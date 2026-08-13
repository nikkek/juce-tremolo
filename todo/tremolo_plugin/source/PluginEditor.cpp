namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {
  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
  logoCenter.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
  logoRight.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  addAndMakeVisible(background);
  addAndMakeVisible(logo);

  addAndMakeVisible(lfoVisualizer);

  rateSlider.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  rateSlider.setPopupDisplayEnabled(true, true, this);
  rateSlider.setRange(1.0, 30.0, 0.5);
  rateSlider.onValueChange = [this] { DBG(rateSlider.getValue()); };
  rateSlider.setTextValueSuffix(" Hz");
  addAndMakeVisible(rateSlider);

  addAndMakeVisible(logoCenter);
  addAndMakeVisible(logoRight);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 270);
}

void PluginEditor::resized() {
  auto bounds = getLocalBounds();

  background.setBounds(bounds);

  logo.setBounds({16, 16, 140, 22});

  lfoVisualizer.setBounds({19, 150, 502, 92});
  // lfoVisualizer.setWaveform(LfoVisualizer::LfoWaveform::triangle);

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromBottom(150);
  rateSlider.setBounds(rateSliderBounds);

  logoCenter.setSize(140, 22);
  logoCenter.setCentrePosition(getWidth() / 2, 16 + 22 / 2);
  logoRight.setBounds(getWidth() - 16 - 140, 16, 140, 22);
}
}  // namespace tremolo
