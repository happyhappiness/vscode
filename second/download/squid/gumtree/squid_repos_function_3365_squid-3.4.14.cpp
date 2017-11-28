void
unlinkdClose(void)
#if _SQUID_WINDOWS_
{

    if (unlinkd_wfd > -1) {
        debugs(2, DBG_IMPORTANT, "Closing unlinkd pipe on FD " << unlinkd_wfd);
        shutdown(unlinkd_wfd, SD_BOTH);
        comm_close(unlinkd_wfd);

        if (unlinkd_wfd != unlinkd_rfd)
            comm_close(unlinkd_rfd);

        unlinkd_wfd = -1;

        unlinkd_rfd = -1;
    }

    if (hIpc) {
        if (WaitForSingleObject(hIpc, 5000) != WAIT_OBJECT_0) {
            getCurrentTime();
            debugs(2, DBG_IMPORTANT, "unlinkdClose: WARNING: (unlinkd," << pid << "d) didn't exit in 5 seconds");
        }

        CloseHandle(hIpc);
    }
}