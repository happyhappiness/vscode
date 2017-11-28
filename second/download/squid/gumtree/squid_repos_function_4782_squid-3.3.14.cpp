static FILE *
storeCossDirOpenTmpSwapLog(CossSwapDir * sd, int *clean_flag, int *zero_flag)
{
    char *swaplog_path = xstrdup(storeCossDirSwapLogFile(sd, NULL));
    char *clean_path = xstrdup(storeCossDirSwapLogFile(sd, ".last-clean"));
    char *new_path = xstrdup(storeCossDirSwapLogFile(sd, ".new"));

    struct stat log_sb;

    struct stat clean_sb;
    FILE *fp;
    int anfd;

    if (::stat(swaplog_path, &log_sb) < 0) {
        debugs(50, DBG_IMPORTANT, "Cache COSS Dir #" << sd->index << ": No log file");
        safe_free(swaplog_path);
        safe_free(clean_path);
        safe_free(new_path);
        return NULL;
    }

    *zero_flag = log_sb.st_size == 0 ? 1 : 0;
    /* close the existing write-only FD */

    if (sd->swaplog_fd >= 0)
        file_close(sd->swaplog_fd);

    /* open a write-only FD for the new log */
    anfd = file_open(new_path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);

    if (anfd < 0) {
        debugs(50, DBG_IMPORTANT, "" << new_path << ": " << xstrerror());
        fatal("storeDirOpenTmpSwapLog: Failed to open swap log.");
    }

    sd->swaplog_fd = anfd;
    /* open a read-only stream of the old log */
    fp = fopen(swaplog_path, "rb");

    if (fp == NULL) {
        debugs(50, DBG_CRITICAL, "" << swaplog_path << ": " << xstrerror());
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