void
CommIO::Initialize()
{
    if (CommIO::Initialized)
        return;

    /* Initialize done pipe signal */
    int DonePipe[2];
    if (pipe(DonePipe)) {}
    DoneFD = DonePipe[1];
    DoneReadFD = DonePipe[0];
    fd_open(DoneReadFD, FD_PIPE, "async-io completion event: main");
    fd_open(DoneFD, FD_PIPE, "async-io completion event: threads");
    commSetNonBlocking(DoneReadFD);
    commSetNonBlocking(DoneFD);
    Comm::SetSelect(DoneReadFD, COMM_SELECT_READ, NULLFDHandler, NULL, 0);
    Initialized = true;
}