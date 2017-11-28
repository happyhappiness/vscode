void
Ipc::TypedMsgHdr::putRaw(const void *raw, size_t size)
{
    if (size > 0) {
        Must(size <= sizeof(data.raw) - data.size);
        memcpy(data.raw + data.size, raw, size);
        data.size += size;
    }
}