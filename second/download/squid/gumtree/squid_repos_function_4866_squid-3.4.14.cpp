int
CossSwapDir::writeCleanStart()
{
    CossCleanLog *state = new CossCleanLog(this);
#if HAVE_FCHMOD

    struct stat sb;
#endif

    state->newLog = xstrdup(storeCossDirSwapLogFile(this, ".clean"));
    state->fd = file_open(state->newLog, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);
    cleanLog = NULL;

    if (state->fd < 0) {
        xfree(state->newLog);
        delete state;
        return -1;
    }

    state->cur = xstrdup(storeCossDirSwapLogFile(this, NULL));
    state->cln = xstrdup(storeCossDirSwapLogFile(this, ".last-clean"));
    state->outbuf = (char *)xcalloc(CLEAN_BUF_SZ, 1);
    state->outbuf_offset = 0;
    ::unlink(state->cln);
    state->current = cossindex.tail;
    debugs(50, 3, "storeCOssDirWriteCleanLogs: opened " << state->newLog << ", FD " << state->fd);
#if HAVE_FCHMOD

    if (::stat(state->cur, &sb) == 0)
        fchmod(state->fd, sb.st_mode);

#endif

    cleanLog = state;

    return 0;
}