void Adaptation::Icap::ModXact::writeSomeBody(const char *label, size_t size)
{
    Must(!writer && state.writing < state.writingAlmostDone);
    Must(virgin.body_pipe != NULL);
    debugs(93, 8, HERE << "will write up to " << size << " bytes of " <<
           label);

    MemBuf writeBuf; // TODO: suggest a min size based on size and lastChunk

    writeBuf.init(); // note: we assume that last-chunk will fit

    const size_t writableSize = virginContentSize(virginBodyWriting);
    const size_t chunkSize = min(writableSize, size);

    if (chunkSize) {
        debugs(93, 7, HERE << "will write " << chunkSize <<
               "-byte chunk of " << label);

        openChunk(writeBuf, chunkSize, false);
        writeBuf.append(virginContentData(virginBodyWriting), chunkSize);
        closeChunk(writeBuf);

        virginBodyWriting.progress(chunkSize);
        virginConsume();
    } else {
        debugs(93, 7, HERE << "has no writable " << label << " content");
    }

    const bool wroteEof = virginBodyEndReached(virginBodyWriting);
    bool lastChunk = wroteEof;
    if (state.writing == State::writingPreview) {
        preview.wrote(chunkSize, wroteEof); // even if wrote nothing
        lastChunk = lastChunk || preview.done();
    }

    if (lastChunk) {
        debugs(93, 8, HERE << "will write last-chunk of " << label);
        addLastRequestChunk(writeBuf);
    }

    debugs(93, 7, HERE << "will write " << writeBuf.contentSize()
           << " raw bytes of " << label);

    if (writeBuf.hasContent()) {
        scheduleWrite(writeBuf); // comm will free the chunk
    } else {
        writeBuf.clean();
    }
}