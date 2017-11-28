void
Ipc::StoreMap::abortIo(const sfileno fileno)
{
    debugs(54, 5, HERE << " abort I/O for slot at " << fileno <<
           " in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];

    // The caller is a lock holder. Thus, if we are Writeable, then the
    // caller must be the writer; otherwise the caller must be the reader.
    if (s.state == Slot::Writeable)
        abortWriting(fileno);
    else
        closeForReading(fileno);
}