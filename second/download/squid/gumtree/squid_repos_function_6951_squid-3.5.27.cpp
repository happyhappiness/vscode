static SBuf
StoreMapSlicesId(const SBuf &path)
{
    return Ipc::Mem::Segment::Name(path, "slices");
}