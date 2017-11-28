void
CossState::read_(char *buf, size_t size, off_t offset, STRCB * callback, void *callback_data)
{
    char *p;
    CossSwapDir *SD = (CossSwapDir *)INDEXSD(swap_dirn);

    ++ StoreFScoss::GetInstance().stats.read.ops;
    assert(read.callback == NULL);
    assert(read.callback_data == NULL);
    read.callback = callback;
    read.callback_data = cbdataReference(callback_data);
    debugs(79, 3, "storeCossRead: offset " << offset);
    offset_ = offset;
    flags.reading = true;

    if ((offset + (off_t)size) > st_size)
        size = st_size - offset;

    requestlen = size;

    requestbuf = buf;

    requestoffset = offset;

    if (readbuffer == NULL) {
        p = SD->storeCossMemPointerFromDiskOffset(SD->storeCossFilenoToDiskOffset(swap_filen), NULL);
        sfileno tempReqdiskoffset = reqdiskoffset;
        reqdiskoffset = 0;	/* XXX */
        SD->theFile->read(new CossRead(ReadRequest(p, st_size, tempReqdiskoffset), this));
    } else {
        /*
         * It was copied from memory in storeCossOpen()
         */
        ReadRequest::Pointer readRequest = new CossRead(ReadRequest(
                    (char *)readbuffer,st_size, 0), this);
        SD->readCompleted(readbuffer, st_size, 0, readRequest);
    }
}