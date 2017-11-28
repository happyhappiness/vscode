ConfigOption *
Rock::SwapDir::getOptionTree() const
{
    ConfigOption *copt = ::SwapDir::getOptionTree();
    ConfigOptionVector *vector = dynamic_cast<ConfigOptionVector*>(copt);
    if (vector) {
        // if copt is actually a ConfigOptionVector
        vector->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::parseSizeOption, &SwapDir::dumpSizeOption));
        vector->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::parseTimeOption, &SwapDir::dumpTimeOption));
        vector->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::parseRateOption, &SwapDir::dumpRateOption));
    } else {
        // we don't know how to handle copt, as it's not a ConfigOptionVector.
        // free it (and return nullptr)
        delete copt;
        copt = nullptr;
    }
    return copt;
}