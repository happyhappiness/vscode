const Ipc::MemMap::Slot *
Ipc::MemMap::peekAtReader(const sfileno fileno) const
{
    assert(valid(fileno));
    const Slot &s = shared->slots[fileno];
    if (s.reading())
        return &s; // immediate access by lock holder so no locking
    if (s.writing())
        return NULL; // cannot read the slot when it is being written
    assert(false); // must be locked for reading or writing
    return NULL;
}