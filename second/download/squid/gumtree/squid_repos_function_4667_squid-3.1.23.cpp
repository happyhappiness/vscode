FILE *
UFSSwapDir::openTmpSwapLog(int *clean_flag, int *zero_flag)
{
    char *swaplog_path = xstrdup(logFile(NULL));
    char *clean_path = xstrdup(logFile(".last-clean"));
    char *new_path = xstrdup(logFile(".new"));

    struct stat log_sb;

    struct stat clean_sb;
    FILE *fp;
    int fd;

    if (::stat(swaplog_path, &log_sb) < 0) {
        debugs(47, 1, "Cache Dir #" << index << ": No log file");
        safe_free(swaplog_path);
        safe_free(clean_path);
        safe_free(new_path);
        return NULL;
    }

    *zero_flag = log_sb.st_size == 0 ? 1 : 0;
    /* close the existing write-only FD */

    if (swaplog_fd >= 0)
        file_close(swaplog_fd);

    /* open a write-only FD for the new log */
    fd = file_open(new_path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);

    if (fd < 0) {
        debugs(50, 1, "" << new_path << ": " << xstrerror());
        fatal("storeDirOpenTmpSwapLog: Failed to open swap log.");
    }

    swaplog_fd = fd;

    {
        const StoreSwapLogHeader header;
        MemBuf buf;
        buf.init(header.record_size, header.record_size);
        buf.append(reinterpret_cast<const char*>(&header), sizeof(header));
        // Pad to keep in sync with UFSSwapDir::writeCleanStart().
        // TODO: When MemBuf::spaceSize() is fixed not to subtract one,
        // memset() space() with zeroes and use spaceSize() below.
        buf.appended(static_cast<size_t>(header.record_size) - sizeof(header));
        file_write(swaplog_fd, -1, buf.content(), buf.contentSize(),
                   NULL, NULL, buf.freeFunc());
    }

    /* open a read-only stream of the old log */
    fp = fopen(swaplog_path, "rb");

    if (fp == NULL) {
        debugs(50, 0, "" << swaplog_path << ": " << xstrerror());
        fatal("Failed to open swap log for reading");
    }

    memset(&clean_sb, '\0', sizeof(struct stat));

    if (::stat(clean_path, &clean_sb) < 0)
        *clean_flag = 0;
    else if (clean_sb.st_mtime < log_sb.st_mtime)
        *clean_flag = 0;
    else
        *clean_flag = 1;

    safeunlink(clean_path, 1);

    safe_free(swaplog_path);

    safe_free(clean_path);

    safe_free(new_path);

    return fp;
}