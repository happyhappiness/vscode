void
Rock::IoState::close(int how)
{
    debugs(79, 3, swap_filen << " offset: " << offset_ << " how: " << how <<
           " buf: " << theBuf.size << " callback: " << callback);

    if (!theFile) {
        debugs(79, 3, "I/O already canceled");
        assert(!callback);
        // We keep writeableAnchor_ after callBack() on I/O errors.
        assert(!readableAnchor_);
        return;
    }

    switch (how) {
    case wroteAll:
        assert(theBuf.size > 0); // we never flush last bytes on our own
        writeToDisk(-1); // flush last, yet unwritten slot to disk
        return; // writeCompleted() will callBack()

    case writerGone:
        assert(writeableAnchor_);
        dir->writeError(*e); // abort a partially stored entry
        finishedWriting(DISK_ERROR);
        return;

    case readerDone:
        callBack(0);
        return;
    }
}