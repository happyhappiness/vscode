int
UFSSwapDir::writeCleanStart()
{
    UFSCleanLog *state = new UFSCleanLog(this);
    StoreSwapLogHeader header;
#if HAVE_FCHMOD

    struct stat sb;
#endif

    cleanLog = NULL;
    state->newLog = xstrdup(logFile(".clean"));
    state->fd = file_open(state->newLog, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);

    if (state->fd < 0) {
        xfree(state->newLog);
        delete state;
        return -1;
    }

    state->cur = xstrdup(logFile(NULL));
    state->cln = xstrdup(logFile(".last-clean"));
    state->outbuf = (char *)xcalloc(CLEAN_BUF_SZ, 1);
    state->outbuf_offset = 0;
    /*copy the header */
    xmemcpy(state->outbuf, &header, sizeof(StoreSwapLogHeader));
    // Leave a gap to keep in sync with UFSSwapDir::openTmpSwapLog().
    state->outbuf_offset += header.record_size;

    state->walker = repl->WalkInit(repl);
    ::unlink(state->cln);
    debugs(47, 3, "storeDirWriteCleanLogs: opened " << state->newLog << ", FD " << state->fd);
#if HAVE_FCHMOD

    if (::stat(state->cur, &sb) == 0)
        fchmod(state->fd, sb.st_mode);

#endif


    cleanLog = state;
    return 0;
}