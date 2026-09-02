namespace tremolo {
class MessageOnClick : public juce::MouseListener {
public:
  ~MessageOnClick() override {
    if (parent != nullptr)
      parent->removeMouseListener(this);
  }

  void setComponentToListenTo(juce::Component& component) {
    parent = &component;
    component.addMouseListener(this, false);
  }

  void mouseDoubleClick(const juce::MouseEvent& event) override {
    DBG("bubble");

    juce::AttributedString text(juce::String(JucePlugin_Manufacturer) + "\n" +
                                JucePlugin_Name + "\n" + "Build: " + __DATE__ +
                                " " + __TIME__ + "\n" +
                                "Version: " + JucePlugin_VersionString);

    text.setColour(juce::Colours::beige);
    text.setFont(CustomLookAndFeel::getSideLabelFonts());

    parent->getParentComponent()->addAndMakeVisible(bubble);
    bubble.showAt(parent, text, 5000);
  };

private:
  juce::Component* parent = nullptr;
  juce::BubbleMessageComponent bubble;
};
}  // namespace tremolo