void
Rock::HeaderUpdater::parseReadBytes()
{
    if (!staleSwapHeaderSize) {
        StoreMetaUnpacker aBuilder(
            exchangeBuffer.rawContent(),
            exchangeBuffer.length(),
            &staleSwapHeaderSize);
        // Squid assumes that metadata always fits into a single db slot
        aBuilder.checkBuffer(); // cannot update an entry with invalid metadata
        debugs(47, 7, "staleSwapHeaderSize=" << staleSwapHeaderSize);
        Must(staleSwapHeaderSize > 0);
        exchangeBuffer.consume(staleSwapHeaderSize);
    }

    const size_t staleHttpHeaderSize = headersEnd(
                                           exchangeBuffer.rawContent(),
                                           exchangeBuffer.length());
    debugs(47, 7, "staleHttpHeaderSize=" << staleHttpHeaderSize);
    if (!staleHttpHeaderSize) {
        readMore("need more stale HTTP reply header data");
        return;
    }

    exchangeBuffer.consume(staleHttpHeaderSize);
    debugs(47, 7, "httpBodySizePrefix=" << exchangeBuffer.length());

    stopReading("read the last HTTP header slot");
    startWriting();
}