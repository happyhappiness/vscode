static void
logfileHandleWrite(int fd, void *data)
{
    Logfile *lf = (Logfile *) data;
    l_daemon_t *ll = (l_daemon_t *) lf->data;
    int ret;
    logfile_buffer_t *b;

    /*
     * We'll try writing the first entry until its done - if we
     * get a partial write then we'll re-schedule until its completed.
     * Its naive but it'll do for now.
     */
    b = static_cast<logfile_buffer_t*>(ll->bufs.head->data);
    assert(b != NULL);
    ll->flush_pending = 0;

    ret = FD_WRITE_METHOD(ll->wfd, b->buf + b->written_len, b->len - b->written_len);
    debugs(50, 3, "logfileHandleWrite: " << lf->path << ": write returned " << ret);
    if (ret < 0) {
        if (ignoreErrno(errno)) {
            /* something temporary */
            goto reschedule;
        }
        debugs(50, DBG_IMPORTANT,"logfileHandleWrite: " << lf->path << ": error writing (" << xstrerror() << ")");
        /* XXX should handle this better */
        fatal("I don't handle this error well!");
    }
    if (ret == 0) {
        /* error? */
        debugs(50, DBG_IMPORTANT, "logfileHandleWrite: " << lf->path << ": wrote 0 bytes?");
        /* XXX should handle this better */
        fatal("I don't handle this error well!");
    }
    /* ret > 0, so something was written */
    b->written_len += ret;
    assert(b->written_len <= b->len);
    if (b->written_len == b->len) {
        /* written the whole buffer! */
        logfileFreeBuffer(lf, b);
        b = NULL;
    }
    /* Is there more to write? */
    if (ll->bufs.head == NULL) {
        goto finish;
    }
    /* there is, so schedule more */

reschedule:
    Comm::SetSelect(ll->wfd, COMM_SELECT_WRITE, logfileHandleWrite, lf, 0);
    ll->flush_pending = 1;
finish:
    return;
}