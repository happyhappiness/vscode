void
Ipc::TypedMsgHdr::putFixed(const void *rawBuf, size_t rawSize)
{
    // no need to store size because it is constant
    putRaw(rawBuf, rawSize);
}