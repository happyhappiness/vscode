void
Fs::Ufs::UFSSwapDir::closeTmpSwapLog()
{
    assert(rebuilding_);
    rebuilding_ = false;

    char *swaplog_path = xstrdup(logFile(NULL)); // where the swaplog should be
    char *tmp_path = xstrdup(logFile(".new")); // the temporary file we have generated
    int fd;
    file_close(swaplog_fd);

    if (xrename(tmp_path, swaplog_path) < 0) {
        fatalf("Failed to rename log file %s to %s", tmp_path, swaplog_path);
    }

    fd = file_open(swaplog_path, O_WRONLY | O_CREAT | O_BINARY);

    if (fd < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "ERROR: " << swaplog_path << ": " << xstrerr(xerrno));
        fatalf("Failed to open swap log %s", swaplog_path);
    }

    xfree(swaplog_path);
    xfree(tmp_path);
    swaplog_fd = fd;
    debugs(47, 3, "Cache Dir #" << index << " log opened on FD " << fd);
}