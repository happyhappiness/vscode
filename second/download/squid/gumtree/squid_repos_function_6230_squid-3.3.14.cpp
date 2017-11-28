void
Ipc::TypedMsgHdr::putFixed(const void *raw, size_t size)
{
    // no need to store size because it is constant
    putRaw(raw, size);
}