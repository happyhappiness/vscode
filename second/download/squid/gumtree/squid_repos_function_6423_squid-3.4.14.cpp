void
Ipc::StoreMap::abortWriting(const sfileno fileno)
{
    debugs(54, 5, HERE << " abort writing slot at " << fileno <<
           " in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];
    assert(s.state == Slot::Writeable);
    freeLocked(s, false);
}