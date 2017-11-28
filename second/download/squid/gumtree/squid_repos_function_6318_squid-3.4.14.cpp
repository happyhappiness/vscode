void
Ipc::TypedMsgHdr::putRaw(const void *rawBuf, size_t rawSize)
{
    if (rawSize > 0) {
        Must(rawSize <= sizeof(data.raw) - data.size);
        memcpy(data.raw + data.size, rawBuf, rawSize);
        data.size += rawSize;
    }
}