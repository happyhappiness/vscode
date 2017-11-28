void Adaptation::Icap::ModXact::closeChunk(MemBuf &buf)
{
    buf.append(ICAP::crlf, 2); // chunk-terminating CRLF
}