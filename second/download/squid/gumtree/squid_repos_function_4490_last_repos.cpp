int64_t
Store::Disk::minObjectSize() const
{
    // per-store min-size=N value is authoritative
    return min_objsize > -1 ? min_objsize : Config.Store.minObjectSize;
}