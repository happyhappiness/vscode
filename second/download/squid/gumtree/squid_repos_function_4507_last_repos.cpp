ConfigOption *
Store::Disk::getOptionTree() const
{
    ConfigOptionVector *result = new ConfigOptionVector;
    result->options.push_back(new ConfigOptionAdapter<Disk>(*const_cast<Disk*>(this), &Store::Disk::optionReadOnlyParse, &Store::Disk::optionReadOnlyDump));
    result->options.push_back(new ConfigOptionAdapter<Disk>(*const_cast<Disk*>(this), &Store::Disk::optionObjectSizeParse, &Store::Disk::optionObjectSizeDump));
    return result;
}