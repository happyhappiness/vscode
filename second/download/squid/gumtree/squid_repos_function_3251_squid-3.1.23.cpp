void
unlinkdClose(void)
#ifdef _SQUID_MSWIN_
{

    if (unlinkd_wfd > -1) {
        debugs(2, 1, "Closing unlinkd pipe on FD " << unlinkd_wfd);
        shutdown(unlinkd_wfd, SD_BOTH);
        comm_close(unlinkd_wfd);

        if (unlinkd_wfd != unlinkd_rfd)
            comm_close(unlinkd_rfd);

        unlinkd_wfd = -1;

        unlinkd_rfd = -1;
    } else
        debugs(2, 0, "unlinkdClose: WARNING: unlinkd_wfd is " << unlinkd_wfd);

    if (hIpc) {
        if (WaitForSingleObject(hIpc, 5000) != WAIT_OBJECT_0) {
            getCurrentTime();
            debugs(2, 1, "unlinkdClose: WARNING: (unlinkd," << pid << "d) didn't exit in 5 seconds");
        }

        CloseHandle(hIpc);
    }
}