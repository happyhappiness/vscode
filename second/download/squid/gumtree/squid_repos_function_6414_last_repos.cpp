ConfigOption *
DiskdIOStrategy::getOptionTree() const
{
    ConfigOptionVector *result = new ConfigOptionVector;
    result->options.push_back(new ConfigOptionAdapter<DiskdIOStrategy>(*const_cast<DiskdIOStrategy *>(this), &DiskdIOStrategy::optionQ1Parse, &DiskdIOStrategy::optionQ1Dump));
    result->options.push_back(new ConfigOptionAdapter<DiskdIOStrategy>(*const_cast<DiskdIOStrategy *>(this), &DiskdIOStrategy::optionQ2Parse, &DiskdIOStrategy::optionQ2Dump));
    return result;
}