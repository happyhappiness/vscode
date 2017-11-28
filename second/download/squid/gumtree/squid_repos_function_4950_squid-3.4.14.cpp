void
Rock::IoState::startWriting()
{
    assert(theFile != NULL);
    assert(!theBuf.isNull());

    // TODO: if DiskIO module is mmap-based, we should be writing whole pages
    // to avoid triggering read-page;new_head+old_tail;write-page overheads

    debugs(79, 5, HERE << swap_filen << " at " << diskOffset << '+' <<
           theBuf.contentSize());

    assert(theBuf.contentSize() <= slotSize);
    // theFile->write may call writeCompleted immediatelly
    theFile->write(new WriteRequest(::WriteRequest(theBuf.content(),
                                    diskOffset, theBuf.contentSize(), theBuf.freeFunc()), this));
}