SBuf
Rock::SwapDir::inodeMapPath() const
{
    return Ipc::Mem::Segment::Name(SBuf(path), "map");
}