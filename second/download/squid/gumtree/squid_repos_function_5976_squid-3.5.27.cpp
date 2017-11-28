int
logfile_mod_daemon_open(Logfile * lf, const char *path, size_t bufsz, int fatal_flag)
{
    const char *args[5];
    char *tmpbuf;
    l_daemon_t *ll;

    lf->f_close = logfile_mod_daemon_close;
    lf->f_linewrite = logfile_mod_daemon_writeline;
    lf->f_linestart = logfile_mod_daemon_linestart;
    lf->f_lineend = logfile_mod_daemon_lineend;
    lf->f_flush = logfile_mod_daemon_flush;
    lf->f_rotate = logfile_mod_daemon_rotate;

    cbdataInternalLock(lf); // WTF?
    debugs(50, DBG_IMPORTANT, "Logfile Daemon: opening log " << path);
    ll = static_cast<l_daemon_t*>(xcalloc(1, sizeof(*ll)));
    lf->data = ll;
    ll->eol = 1;
    {
        Ip::Address localhost;
        args[0] = "(logfile-daemon)";
        args[1] = path;
        args[2] = NULL;
        localhost.setLocalhost();
        ll->pid = ipcCreate(IPC_STREAM, Log::TheConfig.logfile_daemon, args, "logfile-daemon", localhost, &ll->rfd, &ll->wfd, NULL);
        if (ll->pid < 0)
            fatal("Couldn't start logfile helper");
    }
    ll->nbufs = 0;

    /* Queue the initial control data */
    tmpbuf = static_cast<char*>(xmalloc(BUFSIZ));
    snprintf(tmpbuf, BUFSIZ, "r%d\nb%d\n", Config.Log.rotateNumber, Config.onoff.buffered_logs);
    logfile_mod_daemon_append(lf, tmpbuf, strlen(tmpbuf));
    xfree(tmpbuf);

    /* Start the flush event */
    eventAdd("logfileFlush", logfileFlushEvent, lf, 1.0, 1);

    return 1;
}