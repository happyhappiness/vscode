void
Fs::Ufs::UFSStoreState::read_(char *buf, size_t size, off_t aOffset, STRCB * aCallback, void *aCallbackData)
{
    assert(read.callback == NULL);
    assert(read.callback_data == NULL);
    assert(!reading);
    assert(!closing);
    assert (aCallback);

    if (!theFile->canRead()) {
        debugs(79, 3, "UFSStoreState::read_: queueing read because theFile can't read");
        queueRead (buf, size, aOffset, aCallback, aCallbackData);
        return;
    }

    read.callback = aCallback;
    read.callback_data = cbdataReference(aCallbackData);
    debugs(79, 3, "UFSStoreState::read_: dirno " << swap_dirn  << ", fileno "<<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << swap_filen);
    offset_ = aOffset;
    read_buf = buf;
    reading = true;
    theFile->read(new ReadRequest(buf,aOffset,size));
}