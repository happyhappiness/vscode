                   NULL, NULL, buf.freeFunc());
    }

    /* open a read-only stream of the old log */
    fp = fopen(swaplog_path, "rb");

    if (!fp) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "ERROR: while opening " << swaplog_path << ": " << xstrerr(xerrno));
        fatalf("Failed to open swap log for reading %s", swaplog_path);
    }

    memset(&clean_sb, '\0', sizeof(struct stat));

    if (::stat(clean_path, &clean_sb) < 0)
