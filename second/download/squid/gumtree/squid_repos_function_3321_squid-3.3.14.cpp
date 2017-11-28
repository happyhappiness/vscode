void
unlinkdInit(void)
{
    if (unlinkd_wfd >= 0)
        return; // unlinkd already started

    const char *args[2];
    Ip::Address localhost;

    args[0] = "(unlinkd)";
    args[1] = NULL;
    localhost.SetLocalhost();

    pid = ipcCreate(
#if USE_POLL && _SQUID_OSF_
              /* pipes and poll() don't get along on DUNIX -DW */
              IPC_STREAM,
#elif _SQUID_WINDOWS_
              /* select() will fail on a pipe */
              IPC_TCP_SOCKET,
#else
              /* We currently need to use FIFO.. see below */
              IPC_FIFO,
#endif
              Config.Program.unlinkd,
              args,
              "unlinkd",
              localhost,
              &unlinkd_rfd,
              &unlinkd_wfd,
              &hIpc);

    if (pid < 0)
        fatal("Failed to create unlinkd subprocess");

    xusleep(250000);

    fd_note(unlinkd_wfd, "squid -> unlinkd");

    fd_note(unlinkd_rfd, "unlinkd -> squid");

    commUnsetFdTimeout(unlinkd_rfd);
    commUnsetFdTimeout(unlinkd_wfd);

    /*
    * unlinkd_rfd should already be non-blocking because of
    * ipcCreate.  We change unlinkd_wfd to blocking mode because
    * we never want to lose an unlink request, and we don't have
    * code to retry if we get EWOULDBLOCK.  Unfortunately, we can
    * do this only for the IPC_FIFO case.
    */
    assert(fd_table[unlinkd_rfd].flags.nonblocking);

    if (FD_PIPE == fd_table[unlinkd_wfd].type)
        commUnsetNonBlocking(unlinkd_wfd);

    debugs(2, DBG_IMPORTANT, "Unlinkd pipe opened on FD " << unlinkd_wfd);

#if _SQUID_WINDOWS_

    debugs(2, 4, "Unlinkd handle: 0x" << std::hex << hIpc << std::dec << ", PID: " << pid);

#endif

}