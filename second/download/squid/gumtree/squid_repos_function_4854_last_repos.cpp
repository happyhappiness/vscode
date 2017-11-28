void
Http::Stream::packChunk(const StoreIOBuffer &bodyData, MemBuf &mb)
{
    const uint64_t length =
        static_cast<uint64_t>(lengthToSend(bodyData.range()));
    noteSentBodyBytes(length);

    mb.appendf("%" PRIX64 "\r\n", length);
    mb.append(bodyData.data, length);
    mb.append("\r\n", 2);
}