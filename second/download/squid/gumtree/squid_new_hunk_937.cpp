    openChunk(buf, 0, ieof);
    closeChunk(buf);
}

void Adaptation::Icap::ModXact::openChunk(MemBuf &buf, size_t chunkSize, bool ieof)
{
    buf.appendf((ieof ? "%x; ieof\r\n" : "%x\r\n"), (int) chunkSize);
}

void Adaptation::Icap::ModXact::closeChunk(MemBuf &buf)
{
    buf.append(ICAP::crlf, 2); // chunk-terminating CRLF
}
