void
HelperServerBase::closePipesSafely()
{
#if _SQUID_WINDOWS_
    int no = index + 1;

    shutdown(writePipe->fd, SD_BOTH);
#endif

    flags.closing = 1;
    if (readPipe->fd == writePipe->fd)
        readPipe->fd = -1;
    else
        readPipe->close();
    writePipe->close();

#if _SQUID_WINDOWS_
    if (hIpc) {
        if (WaitForSingleObject(hIpc, 5000) != WAIT_OBJECT_0) {
            getCurrentTime();
            debugs(84, DBG_IMPORTANT, "WARNING: " << hlp->id_name <<
                   " #" << no << " (" << hlp->cmdline->key << "," <<
                   (long int)pid << ") didn't exit in 5 seconds");
        }
        CloseHandle(hIpc);
    }
#endif
}