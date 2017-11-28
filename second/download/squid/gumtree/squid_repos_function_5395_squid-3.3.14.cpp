static void
logfile_mod_daemon_lineend(Logfile * lf)
{
    l_daemon_t *ll = static_cast<l_daemon_t *>(lf->data);
    logfile_buffer_t *b;
    assert(ll->eol == 0);
    ll->eol = 1;
    /* Kick a write off if the head buffer is -full- */
    if (ll->bufs.head != NULL) {
        b = static_cast<logfile_buffer_t*>(ll->bufs.head->data);
        if (b->node.next != NULL || !Config.onoff.buffered_logs)
            logfileQueueWrite(lf);
    }
}