int64_t
Rock::SwapDir::diskOffset(Ipc::Mem::PageId &pageId) const
{
    assert(pageId);
    return diskOffset(pageId.number - 1);
}