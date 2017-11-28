void
Ipc::TypedMsgHdr::getRaw(void *rawBuf, size_t rawSize) const
{
    if (rawSize > 0) {
        Must(rawSize <= data.size - offset);
        memcpy(rawBuf, data.raw + offset, rawSize);
        offset += rawSize;
    }
}