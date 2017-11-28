
    char *logPath;
    logPath = logFile();
    swaplog_fd = file_open(logPath, O_WRONLY | O_CREAT | O_BINARY);

    if (swaplog_fd < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "ERROR opening swap log " << logPath << ": " << xstrerr(xerrno));
        fatal("UFSSwapDir::openLog: Failed to open swap log.");
    }

    debugs(50, 3, HERE << "Cache Dir #" << index << " log opened on FD " << swaplog_fd);
}

