void
Rock::IoState::read_(char *buf, size_t len, off_t coreOff, STRCB *cb, void *data)
{
    assert(theFile != NULL);
    assert(coreOff >= 0);
    offset_ = coreOff;

    // we skip our cell header; it is only read when building the map
    const int64_t cellOffset = sizeof(DbCellHeader) +
                               static_cast<int64_t>(coreOff);
    assert(cellOffset <= payloadEnd);

    // Core specifies buffer length, but we must not exceed stored entry size
    if (cellOffset + (int64_t)len > payloadEnd)
        len = payloadEnd - cellOffset;

    assert(read.callback == NULL);
    assert(read.callback_data == NULL);
    read.callback = cb;
    read.callback_data = cbdataReference(data);

    theFile->read(new ReadRequest(
                      ::ReadRequest(buf, diskOffset + cellOffset, len), this));
}