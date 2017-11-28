void
Rock::IoState::read_(char *buf, size_t len, off_t coreOff, STRCB *cb, void *data)
{
    debugs(79, 7, swap_filen << " reads from " << coreOff);

    assert(theFile != NULL);
    assert(coreOff >= 0);

    // if we are dealing with the first read or
    // if the offset went backwords, start searching from the beginning
    if (sidCurrent < 0 || coreOff < objOffset) {
        sidCurrent = readAnchor().start;
        objOffset = 0;
    }

    while (sidCurrent >= 0 && coreOff >= objOffset + currentReadableSlice().size) {
        objOffset += currentReadableSlice().size;
        sidCurrent = currentReadableSlice().next;
    }

    assert(read.callback == NULL);
    assert(read.callback_data == NULL);
    read.callback = cb;
    read.callback_data = cbdataReference(data);

    // punt if read offset is too big (because of client bugs or collapsing)
    if (sidCurrent < 0) {
        debugs(79, 5, "no " << coreOff << " in " << *e);
        callReaderBack(buf, 0);
        return;
    }

    offset_ = coreOff;
    len = min(len,
              static_cast<size_t>(objOffset + currentReadableSlice().size - coreOff));
    const uint64_t diskOffset = dir->diskOffset(sidCurrent);
    theFile->read(new ReadRequest(::ReadRequest(buf,
                                  diskOffset + sizeof(DbCellHeader) + coreOff - objOffset, len), this));
}