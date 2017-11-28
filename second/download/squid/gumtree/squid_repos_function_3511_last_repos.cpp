void Adaptation::Icap::ModXact::openChunk(MemBuf &buf, size_t chunkSize, bool ieof)
{
    buf.appendf((ieof ? "%x; ieof\r\n" : "%x\r\n"), (int) chunkSize);
}