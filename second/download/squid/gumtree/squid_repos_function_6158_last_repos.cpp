static void
logfile_mod_daemon_flush(Logfile * lf)
{
    l_daemon_t *ll = static_cast<l_daemon_t *>(lf->data);
    if (commUnsetNonBlocking(ll->wfd)) {
        debugs(50, DBG_IMPORTANT, "Logfile Daemon: Couldn't set the pipe blocking for flush! You're now missing some log entries.");
        return;
    }
    while (ll->bufs.head != NULL) {
        logfileHandleWrite(ll->wfd, lf);
    }
    if (commSetNonBlocking(ll->wfd)) {
        fatalf("Logfile Daemon: %s: Couldn't set the pipe non-blocking for flush!\n", lf->path);
        return;
    }
}