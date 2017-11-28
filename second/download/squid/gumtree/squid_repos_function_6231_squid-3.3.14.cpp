void
Ipc::TypedMsgHdr::getRaw(void *raw, size_t size) const
{
    if (size > 0) {
        Must(size <= data.size - offset);
        memcpy(raw, data.raw + offset, size);
        offset += size;
    }
}