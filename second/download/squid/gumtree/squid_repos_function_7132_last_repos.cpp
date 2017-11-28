const Ipc::StoreMap::Anchor *
Ipc::StoreMap::peekAtReader(const sfileno fileno) const
{
    const Anchor &s = anchorAt(fileno);
    if (s.reading())
        return &s; // immediate access by lock holder so no locking
    if (s.writing())
        return NULL; // the caller is not a read lock holder
    assert(false); // must be locked for reading or writing
    return NULL;
}