        fatalf("Failed to rename log file %s to %s", tmp_path, swaplog_path);
    }

    fd = file_open(swaplog_path, O_WRONLY | O_CREAT | O_BINARY);

    if (fd < 0) {
        debugs(50, DBG_IMPORTANT, "ERROR: " << swaplog_path << ": " << xstrerror());
        fatalf("Failed to open swap log %s", swaplog_path);
    }

    xfree(swaplog_path);
    xfree(tmp_path);
    swaplog_fd = fd;
