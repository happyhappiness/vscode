void
Ipc::MemMap::abortWriting(const sfileno fileno)
{
    debugs(54, 5, "abort writing slot at " << fileno <<
           " in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];
    assert(s.writing());
    freeLocked(s, false);
}