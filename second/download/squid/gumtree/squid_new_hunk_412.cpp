{
    char *logPath;
    logPath = storeCossDirSwapLogFile(this, NULL);
    swaplog_fd = file_open(logPath, O_WRONLY | O_CREAT | O_BINARY);

    if (swaplog_fd < 0) {
        debugs(47, DBG_IMPORTANT, "" << logPath << ": " << xstrerror());
        fatal("storeCossDirOpenSwapLog: Failed to open swap log.");
    }

    debugs(47, 3, "Cache COSS Dir #" << index << " log opened on FD " << swaplog_fd);
}

