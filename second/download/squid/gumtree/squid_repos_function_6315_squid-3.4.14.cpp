void
Ipc::TypedMsgHdr::getFixed(void *rawBuf, size_t rawSize) const
{
    // no need to load size because it is constant
    getRaw(rawBuf, rawSize);
}