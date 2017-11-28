        file_close(sd->swaplog_fd);

    /* open a write-only FD for the new log */
    anfd = file_open(new_path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);

    if (anfd < 0) {
        debugs(50, 1, "" << new_path << ": " << xstrerror());
        fatal("storeDirOpenTmpSwapLog: Failed to open swap log.");
    }

    sd->swaplog_fd = anfd;
    /* open a read-only stream of the old log */
    fp = fopen(swaplog_path, "rb");

    if (fp == NULL) {
        debugs(50, 0, "" << swaplog_path << ": " << xstrerror());
        fatal("Failed to open swap log for reading");
    }

    memset(&clean_sb, '\0', sizeof(struct stat));

    if (::stat(clean_path, &clean_sb) < 0)
