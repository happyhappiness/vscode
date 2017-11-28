const unsigned char *
Ssl::Bio::sslFeatures::helloRecord(const MemBuf &buf)
{
    if (helloMsgSize <= 0)
        return NULL;

    if (helloRecordStart + helloMsgSize <= buf.contentSize())
        return reinterpret_cast<const unsigned char *>(buf.content()) + helloRecordStart;

    return NULL;
}