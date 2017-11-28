void
CommIO::ResetNotifications()
{
    if (DoneSignalled) {
        FlushPipe();
        DoneSignalled = false;
    }
}