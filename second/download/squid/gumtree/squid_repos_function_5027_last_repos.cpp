bool
Rock::Rebuild::sameEntry(const sfileno fileno, const DbCellHeader &header) const
{
    // Header updates always result in multi-start chains and often
    // result in multi-version chains so we can only compare the keys.
    const Ipc::StoreMap::Anchor &anchor = sd->map->writeableEntry(fileno);
    return anchor.sameKey(reinterpret_cast<const cache_key*>(header.key));
}