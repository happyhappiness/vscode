void
Fs::Ufs::UFSSwapDir::closeLog()
{
    if (swaplog_fd < 0) /* not open */
        return;

    file_close(swaplog_fd);

    debugs(47, 3, "Cache Dir #" << index << " log closed on FD " << swaplog_fd);

    swaplog_fd = -1;

    --NumberOfUFSDirs;

    assert(NumberOfUFSDirs >= 0);

    if (0 == NumberOfUFSDirs)
        safe_free(UFSDirToGlobalDirMapping);
}