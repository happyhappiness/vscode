void
IpcIoFile::close()
{
    assert(ioRequestor != NULL);

    if (IamDiskProcess())
        DiskerClose(dbName);
    // XXX: else nothing to do?

    ioRequestor->closeCompleted();
}