static void
logfileQueueWrite(Logfile * lf)
{
    l_daemon_t *ll = (l_daemon_t *) lf->data;
    if (ll->flush_pending || ll->bufs.head == NULL) {
        return;
    }
    ll->flush_pending = 1;
    if (ll->bufs.head) {
        logfile_buffer_t *b = static_cast<logfile_buffer_t*>(ll->bufs.head->data);
        if (b->len + 2 <= b->size)
            logfile_mod_daemon_append(lf, "F\n", 2);
    }
    /* Ok, schedule a write-event */
    Comm::SetSelect(ll->wfd, COMM_SELECT_WRITE, logfileHandleWrite, lf, 0);
}