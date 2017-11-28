void
Comm::SelectLoopInit(void)
{
    zero_tv.tv_sec = 0;
    zero_tv.tv_usec = 0;
    FD_ZERO(&global_readfds);
    FD_ZERO(&global_writefds);
    nreadfds = nwritefds = 0;

    Mgr::RegisterAction("comm_select_incoming",
                        "comm_incoming() stats",
                        commIncomingStats, 0, 1);
}