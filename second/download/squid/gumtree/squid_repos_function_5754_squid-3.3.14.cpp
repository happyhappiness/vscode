void
AIODiskFile::close ()
{
    assert (!closed);
#if _SQUID_WINDOWS_
    aio_close(fd);
#else
    file_close(fd);
#endif

    fd = -1;
    closed = true;
    assert (ioRequestor != NULL);
    ioRequestor->closeCompleted();
}