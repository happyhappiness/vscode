ConfigOption *
SwapDir::getOptionTree() const
{
    ConfigOptionVector *result = new ConfigOptionVector;
    result->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::optionReadOnlyParse, &SwapDir::optionReadOnlyDump));
    result->options.push_back(new ConfigOptionAdapter<SwapDir>(*const_cast<SwapDir *>(this), &SwapDir::optionObjectSizeParse, &SwapDir::optionObjectSizeDump));
    return result;
}