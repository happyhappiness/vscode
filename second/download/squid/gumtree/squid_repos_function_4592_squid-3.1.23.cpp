void
CossSwapDir::closeLog()
{
    if (swaplog_fd < 0)	/* not open */
        return;

    file_close(swaplog_fd);

    debugs(47, 3, "Cache COSS Dir #" << index << " log closed on FD " << swaplog_fd);

    swaplog_fd = -1;
}