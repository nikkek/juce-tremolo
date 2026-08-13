namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p),
      rateAttachment{p.getParameterRefs().rate, rateSlider},
      depthAttachment{p.getParameterRefs().depth, depthSlider},
      depthAttachment2{p.getParameterRefs().depth, depthSlider2} {
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
  rateSlider.setTextValueSuffix(" Hz");
  addAndMakeVisible(rateSlider);

  depthSlider.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  depthSlider.setPopupDisplayEnabled(true, true, this);
  addAndMakeVisible(depthSlider);

  depthSlider2.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  depthSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  depthSlider2.setPopupDisplayEnabled(true, true, this);
  addAndMakeVisible(depthSlider2);

  lfoCurveWidthSlider.setRange(0.0, 10.0, 1.0);
  lfoCurveWidthSlider.onValueChange = [this] {
    lfoVisualizer.setStrokeWidth(
        static_cast<float>(lfoCurveWidthSlider.getValue()));
  };
  addAndMakeVisible(lfoCurveWidthSlider);

  addAndMakeVisible(logoCenter);
  addAndMakeVisible(logoRight);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 300);
}

void PluginEditor::resized() {
  auto bounds = getLocalBounds();

  background.setBounds({0, 0, bounds.getWidth(), bounds.getHeight() - 30});

  logo.setBounds({16, 16, 140, 22});

  lfoVisualizer.setBounds({19, 150, 502, 92});
  // lfoVisualizer.setWaveform(LfoVisualizer::LfoWaveform::triangle);

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromBottom(150);
  rateSlider.setBounds(rateSliderBounds);

  auto depthSliderBounds = bounds;
  depthSliderBounds.removeFromLeft(130);
  depthSliderBounds.removeFromRight(330);
  depthSliderBounds.removeFromTop(40);
  depthSliderBounds.removeFromBottom(150);
  depthSlider.setBounds(depthSliderBounds);

  auto depthSliderBounds2 = bounds;
  depthSliderBounds2.removeFromLeft(30);
  depthSliderBounds2.removeFromRight(430);
  depthSliderBounds2.removeFromTop(40);
  depthSliderBounds2.removeFromBottom(150);
  depthSlider2.setBounds(depthSliderBounds2);

  auto lfoCurveWidthSliderBounds = bounds;
  lfoCurveWidthSliderBounds.removeFromTop(270);
  lfoCurveWidthSliderBounds.removeFromRight(bounds.getWidth() / 2);
  lfoCurveWidthSlider.setBounds(lfoCurveWidthSliderBounds);

  logoCenter.setSize(140, 22);
  logoCenter.setCentrePosition(getWidth() / 2, 16 + 22 / 2);
  logoRight.setBounds(getWidth() - 16 - 140, 16, 140, 22);
}
}  // namespace tremolo
