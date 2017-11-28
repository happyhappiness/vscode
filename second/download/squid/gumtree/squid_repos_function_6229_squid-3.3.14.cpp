void
Ipc::TypedMsgHdr::getFixed(void *raw, size_t size) const
{
    // no need to load size because it is constant
    getRaw(raw, size);
}