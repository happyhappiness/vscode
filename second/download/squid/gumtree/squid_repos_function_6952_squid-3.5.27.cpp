static SBuf
StoreMapAnchorsId(const SBuf &path)
{
    return Ipc::Mem::Segment::Name(path, "anchors");
}