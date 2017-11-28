void
DelayVector::dump(StoreEntry *entry) const
{
    const_iterator pos = pools.begin();

    while (pos != pools.end()) {
        (*pos)->dump(entry);
        ++pos;
    }
}