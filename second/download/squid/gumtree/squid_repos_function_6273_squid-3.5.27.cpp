void
IpcIoFile::close()
{
    assert(ioRequestor != NULL);

    if (IamDiskProcess())
        DiskerClose(SBuf(dbName.termedBuf()));
    // XXX: else nothing to do?

    ioRequestor->closeCompleted();
}