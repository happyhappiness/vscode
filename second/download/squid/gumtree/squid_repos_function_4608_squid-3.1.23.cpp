static void
storeCossDirCloseTmpSwapLog(CossSwapDir * sd)
{
    char *swaplog_path = xstrdup(storeCossDirSwapLogFile(sd, NULL));
    char *new_path = xstrdup(storeCossDirSwapLogFile(sd, ".new"));
    int anfd;
    file_close(sd->swaplog_fd);

    if (xrename(new_path, swaplog_path) < 0) {
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
    debugs(47, 3, "Cache COSS Dir #" << sd->index << " log opened on FD " << anfd);
}