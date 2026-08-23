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

  bypassLabel.setFont(lookAndFeel.getSideLabelFonts());
  /* bypassLabel.setColour(
      juce::Label::textColourId,
      CustomLookAndFeel::getColor(CustomLookAndFeel::Colors::textColour));*/
  addAndMakeVisible(bypassLabel);

  bypassButton.onClick = [this] {
    bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypassed"
                                                             : "Off");
  };
  bypassButton.onClick();

  addAndMakeVisible(bypassButton);

  waveformLabel.setFont(lookAndFeel.getSideLabelFonts());
  /* waveformLabel.setColour(
      juce::Label::textColourId,
      CustomLookAndFeel::getColor(CustomLookAndFeel::Colors::textColour));*/
  addAndMakeVisible(waveformLabel);

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

  rateLabel.setJustificationType(juce::Justification::centred);
  rateLabel.setInterceptsMouseClicks(false, false);
  rateLabel.setFont(lookAndFeel.getComponentFonts());
  rateLabel.setColour(juce::Label::textColourId, juce::Colours::beige);
  addAndMakeVisible(rateLabel);

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

  /* juce::StringArray lookAndFeelOptions{"Custom", "V2", "V3", "V4"};
  lookAndFeelComboBox.addItemList(lookAndFeelOptions, 1);
  lookAndFeelComboBox.onChange = [this] {
    switch (lookAndFeelComboBox.getSelectedId()) {
      case 1:
        setLookAndFeel(&lookAndFeel);
        break;

      case 2:
        setLookAndFeel(&lookAndFeel_V2);
        break;

      case 3:
        setLookAndFeel(&lookAndFeel_V3);
        break;

      case 4:
        setLookAndFeel(&lookAndFeel_V4);
        break;
    }
  };
  addAndMakeVisible(lookAndFeelComboBox);*/

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

  const auto rateLabelBounds = rateSliderBounds;
  rateLabel.setBounds(rateLabelBounds);

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

  auto bypassButtonBounds = bounds;
  bypassButtonBounds.removeFromTop(66);
  bypassButtonBounds.removeFromRight(16);
  bypassButtonBounds.removeFromLeft(392);
  bypassButtonBounds.removeFromBottom(176);
  bypassButton.setBounds(bypassButtonBounds);

  const auto bypassLabelBounds =
      bypassButtonBounds.translated(0, -bypassButtonBounds.getHeight());
  bypassLabel.setBounds(bypassLabelBounds);

  auto waveformComboBoxBounds = bounds;
  waveformComboBoxBounds.removeFromTop(66);
  waveformComboBoxBounds.removeFromRight(392);
  waveformComboBoxBounds.removeFromLeft(16);
  waveformComboBoxBounds.removeFromBottom(176);
  waveformComboBox.setBounds(waveformComboBoxBounds);

  const auto waveformLabelBounds =
      waveformComboBoxBounds.translated(0, -waveformComboBoxBounds.getHeight());
  waveformLabel.setBounds(waveformLabelBounds);

  auto lookAndFeelComboBoxBounds = bounds;
  lookAndFeelComboBoxBounds.removeFromTop(254);
  lookAndFeelComboBoxBounds.removeFromRight(bounds.getWidth() / 2);
  lookAndFeelComboBoxBounds.removeFromLeft(16);
  lookAndFeelComboBox.setBounds(lookAndFeelComboBoxBounds);
}
}  // namespace tremolo
