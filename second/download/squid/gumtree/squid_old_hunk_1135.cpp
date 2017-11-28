
    logfile_buffer_t *b = static_cast<logfile_buffer_t*>(ll->bufs.head->data);
    assert(b != NULL);
    ll->flush_pending = 0;

    int ret = FD_WRITE_METHOD(ll->wfd, b->buf + b->written_len, b->len - b->written_len);
    debugs(50, 3, lf->path << ": write returned " << ret);
    if (ret < 0) {
        if (ignoreErrno(errno)) {
            /* something temporary */
            Comm::SetSelect(ll->wfd, COMM_SELECT_WRITE, logfileHandleWrite, lf, 0);
            ll->flush_pending = 1;
            return;
        }
        debugs(50, DBG_IMPORTANT,"logfileHandleWrite: " << lf->path << ": error writing (" << xstrerror() << ")");
        /* XXX should handle this better */
        fatal("I don't handle this error well!");
    }
    if (ret == 0) {
        /* error? */
        debugs(50, DBG_IMPORTANT, "logfileHandleWrite: " << lf->path << ": wrote 0 bytes?");
