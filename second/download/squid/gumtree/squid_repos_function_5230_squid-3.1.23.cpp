void
AIODiskFile::close ()
{
    assert (!closed);
#ifdef _SQUID_WIN32_

    aio_close(fd);
#else

    file_close(fd);
#endif

    fd = -1;
    closed = true;
    assert (ioRequestor != NULL);
    ioRequestor->closeCompleted();
}