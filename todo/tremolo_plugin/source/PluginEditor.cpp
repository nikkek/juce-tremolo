namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p),
      rateAttachment{p.getParameterRefs().rate, rateSlider},
      depthAttachment{p.getParameterRefs().depth, depthSlider},
      bypassAttachment{p.getParameterRefs().bypassed, bypassButton},
      waveformAttachment{p.getParameterRefs().waveform, waveformComboBox} {
  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  addAndMakeVisible(background);
  addAndMakeVisible(logo);

  bypassButton.onClick = [this] {
    bypassButton.setButtonText(bypassButton.getToggleState() ? "BYPASSED"
                                                             : "BYPASS");
  };
  bypassButton.onClick();
  addAndMakeVisible(bypassButton);

  waveformComboBox.addItemList(p.getParameterRefs().waveform.choices, 1);
  waveformAttachment.sendInitialUpdate();
  addAndMakeVisible(waveformComboBox);

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

  /* lfoCurveWidthSlider.setRange(0.0, 10.0, 1.0);
  lfoCurveWidthSlider.onValueChange = [this] {
    lfoVisualizer.setStrokeWidth(
        static_cast<float>(lfoCurveWidthSlider.getValue()));
  };
  addAndMakeVisible(lfoCurveWidthSlider);*/

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.

  setLookAndFeel(&lookAndFeel);

  setSize(540, 270);
}

PluginEditor::~PluginEditor() {
  setLookAndFeel(nullptr);
}

void PluginEditor::resized() {
  auto bounds = getLocalBounds();

  background.setBounds({0, 0, bounds.getWidth(), bounds.getHeight()});

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

  /* auto lfoCurveWidthSliderBounds = bounds;
  lfoCurveWidthSliderBounds.removeFromTop(270);
  lfoCurveWidthSliderBounds.removeFromRight(bounds.getWidth() / 2);
  lfoCurveWidthSlider.setBounds(lfoCurveWidthSliderBounds);*/

  auto buttonBounds = bounds;
  buttonBounds.removeFromTop(66);
  buttonBounds.removeFromRight(16);
  buttonBounds.removeFromLeft(392);
  buttonBounds.removeFromBottom(176);
  bypassButton.setBounds(buttonBounds);

  auto waveformComboBoxBounds = bounds;
  waveformComboBoxBounds.removeFromTop(66);
  waveformComboBoxBounds.removeFromRight(392);
  waveformComboBoxBounds.removeFromLeft(16);
  waveformComboBoxBounds.removeFromBottom(176);
  waveformComboBox.setBounds(waveformComboBoxBounds);
}
}  // namespace tremolo
