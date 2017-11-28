        fatal("storeCossDirCloseTmpSwapLog: rename failed");
    }

    anfd = file_open(swaplog_path, O_WRONLY | O_CREAT | O_BINARY);

    if (anfd < 0) {
        debugs(50, 1, "" << swaplog_path << ": " << xstrerror());
        fatal("storeCossDirCloseTmpSwapLog: Failed to open swap log.");
    }

    safe_free(swaplog_path);
    safe_free(new_path);
    sd->swaplog_fd = anfd;
