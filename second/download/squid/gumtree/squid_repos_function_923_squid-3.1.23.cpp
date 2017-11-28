void CommIO::NotifyIOClose()
{
    /* Close done pipe signal */
    FlushPipe();
    close(DoneFD);
    close(DoneReadFD);
    fd_close(DoneFD);
    fd_close(DoneReadFD);
    Initialized = false;
}