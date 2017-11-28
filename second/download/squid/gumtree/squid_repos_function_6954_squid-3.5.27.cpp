int
Ipc::StoreMap::compareVersions(const sfileno fileno, time_t newVersion) const
{
    const Anchor &inode = anchorAt(fileno);

    // note: we do not lock, so comparison may be inacurate

    if (inode.empty())
        return +2;

    if (const time_t diff = newVersion - inode.basics.timestamp)
        return diff < 0 ? -1 : +1;

    return 0;
}