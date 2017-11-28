void
Store::Disk::optionReadOnlyDump(StoreEntry * e) const
{
    if (flags.read_only)
        storeAppendPrintf(e, " no-store");
}