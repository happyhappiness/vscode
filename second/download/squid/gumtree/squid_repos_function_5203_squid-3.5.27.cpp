bool
Rock::Rebuild::sameEntry(const sfileno fileno, const DbCellHeader &header) const
{
    const Ipc::StoreMap::Anchor &anchor = sd->map->writeableEntry(fileno);
    const LoadingEntry &le = entries[fileno];
    // any order will work, but do fast comparisons first:
    return le.version == header.version &&
           anchor.start == static_cast<Ipc::StoreMapSliceId>(header.firstSlot) &&
           anchor.sameKey(reinterpret_cast<const cache_key*>(header.key));
}