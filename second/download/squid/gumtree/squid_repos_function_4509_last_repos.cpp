void
Store::Disk::dumpOptions(StoreEntry * entry) const
{
    ConfigOption *newOption = getOptionTree();

    if (newOption)
        newOption->dump(entry);

    delete newOption;
}