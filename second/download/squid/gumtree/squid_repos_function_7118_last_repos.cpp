static SBuf
StoreMapFileNosId(const SBuf &path)
{
    return Ipc::Mem::Segment::Name(path, "filenos");
}