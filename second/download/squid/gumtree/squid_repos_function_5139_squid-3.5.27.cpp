ConfigOption *
Rock::SwapDir::getOptionTree() const
{
    ConfigOptionVector *vector = dynamic_cast<ConfigOptionVector*>(::SwapDir::getOptionTree());
    assert(vector);
    vector->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::parseSizeOption, &SwapDir::dumpSizeOption));
    vector->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::parseTimeOption, &SwapDir::dumpTimeOption));
    vector->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::parseRateOption, &SwapDir::dumpRateOption));
    return vector;
}