static void
logfile_mod_daemon_close(Logfile * lf)
{
    l_daemon_t *ll = static_cast<l_daemon_t *>(lf->data);
    debugs(50, DBG_IMPORTANT, "Logfile Daemon: closing log " << lf->path);
    logfileFlush(lf);
    if (ll->rfd == ll->wfd)
        comm_close(ll->rfd);
    else {
        comm_close(ll->rfd);
        comm_close(ll->wfd);
    }
    kill(ll->pid, SIGTERM);
    eventDelete(logfileFlushEvent, lf);
    xfree(ll);
    lf->data = NULL;
    cbdataInternalUnlock(lf); // WTF??
}