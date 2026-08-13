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

  addAndMakeVisible(logoCenter);
  addAndMakeVisible(logoRight);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 270);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();

  background.setBounds(bounds);

  logo.setBounds({16, 16, 140, 22});

  lfoVisualizer.setBounds({19,150,502,92});
  //lfoVisualizer.setWaveform(LfoVisualizer::LfoWaveform::triangle);

  logoCenter.setSize(140, 22);
  logoCenter.setCentrePosition(getWidth() / 2, 16 + 22 / 2);
  logoRight.setBounds(getWidth() - 16 - 140, 16, 140, 22);
}
}  // namespace tremolo
