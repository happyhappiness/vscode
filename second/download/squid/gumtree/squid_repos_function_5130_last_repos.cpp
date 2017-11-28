void
Fs::Ufs::UFSSwapDir::closeLog()
{
    if (swaplog_fd < 0) /* not open */
        return;

    --NumberOfUFSDirs;
    assert(NumberOfUFSDirs >= 0);
    if (!NumberOfUFSDirs)
        safe_free(UFSDirToGlobalDirMapping);

    if (rebuilding_) // we cannot close the temporary log used for rebuilding
        return;

    file_close(swaplog_fd);

    debugs(47, 3, "Cache Dir #" << index << " log closed on FD " << swaplog_fd);

    swaplog_fd = -1;
}