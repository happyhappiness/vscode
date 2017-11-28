void
Rock::Rebuild::primeNewEntry(Ipc::StoreMap::Anchor &anchor, const sfileno fileno, const DbCellHeader &header)
{
    anchor.setKey(reinterpret_cast<const cache_key*>(header.key));
    assert(header.firstSlot >= 0);
    anchor.start = -1; // addSlotToEntry() will set it

    assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));

    LoadingEntry le = loadingEntry(fileno);
    le.state(LoadingEntry::leLoading);
    le.version = header.version;
    le.size = 0;
}