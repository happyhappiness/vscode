const Ipc::StoreMap::Slot *
Ipc::StoreMap::peekAtReader(const sfileno fileno) const
{
    assert(valid(fileno));
    const Slot &s = shared->slots[fileno];
    switch (s.state) {
    case Slot::Readable:
        return &s; // immediate access by lock holder so no locking
    case Slot::Writeable:
        return NULL; // cannot read the slot when it is being written
    case Slot::Empty:
        assert(false); // must be locked for reading or writing
    }
    assert(false); // not reachable
    return NULL;
}