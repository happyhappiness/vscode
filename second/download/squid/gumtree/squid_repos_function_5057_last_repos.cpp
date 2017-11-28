void
Rock::HeaderUpdater::startWriting()
{
    writer = store->createUpdateIO(
                 update,
                 nullptr, // unused; see StoreIOState::file_callback
                 &NoteDoneWriting,
                 this);
    Must(writer);

    IoState &rockWriter = dynamic_cast<IoState&>(*writer);
    rockWriter.staleSplicingPointNext = staleSplicingPointNext;

    off_t offset = 0; // current writing offset (for debugging)

    {
        debugs(20, 7, "fresh store meta for " << *update.entry);
        const char *freshSwapHeader = update.entry->getSerialisedMetaData();
        const auto freshSwapHeaderSize = update.entry->mem_obj->swap_hdr_sz;
        Must(freshSwapHeader);
        writer->write(freshSwapHeader, freshSwapHeaderSize, 0, nullptr);
        offset += freshSwapHeaderSize;
        xfree(freshSwapHeader);
    }

    {
        debugs(20, 7, "fresh HTTP header @ " << offset);
        MemBuf *httpHeader = update.entry->mem_obj->getReply()->pack();
        writer->write(httpHeader->content(), httpHeader->contentSize(), -1, nullptr);
        offset += httpHeader->contentSize();
        delete httpHeader;
    }

    {
        debugs(20, 7, "moved HTTP body prefix @ " << offset);
        writer->write(exchangeBuffer.rawContent(), exchangeBuffer.length(), -1, nullptr);
        offset += exchangeBuffer.length();
        exchangeBuffer.clear();
    }

    debugs(20, 7, "wrote " << offset);

    writer->close(StoreIOState::wroteAll); // should call noteDoneWriting()
}