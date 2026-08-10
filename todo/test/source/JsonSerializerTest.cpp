#include <tremolo_plugin/tremolo_plugin.h>
#include <gtest/gtest.h>

namespace tremolo {
TEST(JsonSerializer, SerializeToString) {
  PluginProcessor processor;
  auto& parameters = processor.getParameterRefs();

  parameters.rate = 10.f;
  parameters.bypassed = true;
  parameters.waveform = 1;
  parameters.gain = 0.f;
  parameters.depth = 0.f;

  const juce::String expectedOutput =
      u8R"({
  "__version__": 1,
  "pluginName": "Tremolow",
  "modulationRateHz": 10.0,
  "gain": 0.0,
  "bypassed": true,
  "modulationWaveform": "Triangle",
  "modulationDepth": 0.0
})";
  juce::MemoryBlock block;
  juce::MemoryOutputStream outputStream{block, false};

  JsonSerializer::serialize(parameters, outputStream);
  outputStream.flush();

  const auto result = outputStream.toUTF8().removeCharacters("\r");

  EXPECT_EQ(expectedOutput, result);
}

TEST(JsonSerializer, DeserializeFromString) {
  const juce::String savedParameters =
      u8R"({
  "__version__": 1,
  "pluginName": "Tremolow",
  "modulationRateHz": 10.0,
  "gain": 0.0,
  "bypassed": true,
  "modulationWaveform": "Triangle",
  "modulationDepth": 0.0
})";

  juce::MemoryInputStream inputStream{
      savedParameters.getCharPointer(),
      static_cast<size_t>(savedParameters.length()), false};

  PluginProcessor processor;
  auto& parameters = processor.getParameterRefs();

  const auto result = JsonSerializer::deserialize(inputStream, parameters);

  EXPECT_TRUE(result.wasOk());
  EXPECT_FLOAT_EQ(parameters.rate, 10.f);
  EXPECT_FLOAT_EQ(parameters.gain, 0.f);
  EXPECT_TRUE(parameters.bypassed);
  EXPECT_EQ(juce::String{"Triangle"},
            parameters.waveform.getCurrentChoiceName());
  EXPECT_FLOAT_EQ(parameters.depth, 0.f);
}

TEST(JsonSerializer, DontUpdateParametersWhenWaveformNameIsInvalid) {
  // given
  const juce::String savedParameters =
      u8R"({
  "__version__": 1,
  "pluginName": "Tremolow",
  "modulationRateHz": 10.0,
  "gain": 0.0,
  "bypassed": true,
  "modulationWaveform": "Foo",
  "modulationDepth": 0.0
})";

  juce::MemoryInputStream inputStream{
      savedParameters.getCharPointer(),
      static_cast<size_t>(savedParameters.length()), false};

  PluginProcessor processor;
  auto& parameters = processor.getParameterRefs();

  parameters.waveform = 0;
  parameters.bypassed = false;
  parameters.rate = 5.f;
  parameters.gain = 0.f;
  parameters.depth = 0.0f;

  // when
  const auto result = JsonSerializer::deserialize(inputStream, parameters);

  // then
  EXPECT_TRUE(result.failed());
  EXPECT_FLOAT_EQ(parameters.rate.get(), 5.f);
  EXPECT_FLOAT_EQ(parameters.gain.get(), 0.f);
  EXPECT_FALSE(parameters.bypassed.get());
  EXPECT_EQ(0, parameters.waveform.getIndex());
  EXPECT_FLOAT_EQ(parameters.depth, 0.f);
}
}  // namespace tremolo
