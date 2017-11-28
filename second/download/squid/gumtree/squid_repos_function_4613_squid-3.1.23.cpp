void
CossSwapDir::writeCleanDone()
{
    CossCleanLog *state = (CossCleanLog *)cleanLog;

    if (NULL == state)
        return;

    if (state->fd < 0)
        return;

    if (FD_WRITE_METHOD(state->fd, state->outbuf, state->outbuf_offset) < 0) {
        debugs(50, 0, "storeCossDirWriteCleanLogs: " << state->newLog << ": write: " << xstrerror());
        debugs(50, 0, "storeCossDirWriteCleanLogs: Current swap logfile not replaced.");
        file_close(state->fd);
        state->fd = -1;
        ::unlink(state->newLog);
    }

    safe_free(state->outbuf);
    /*
     * You can't rename open files on Microsoft "operating systems"
     * so we have to close before renaming.
     */
    closeLog();
    /* save the fd value for a later test */
    int anfd = state->fd;
    /* rename */

    if (state->fd >= 0) {
#if defined(_SQUID_OS2_) || defined(_SQUID_WIN32_)
        file_close(state->fd);
        state->fd = -1;

#endif

        xrename(state->newLog, state->cur);
    }

    /* touch a timestamp file if we're not still validating */
    if (StoreController::store_dirs_rebuilding)
        (void) 0;
    else if (anfd < 0)
        (void) 0;
    else
        file_close(file_open(state->cln, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY));

    /* close */
    safe_free(state->cur);

    safe_free(state->newLog);

    safe_free(state->cln);

    if (state->fd >= 0)
        file_close(state->fd);

    state->fd = -1;

    delete state;

    cleanLog = NULL;
}