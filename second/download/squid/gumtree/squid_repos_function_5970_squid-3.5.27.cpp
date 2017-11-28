static void
logfileNewBuffer(Logfile * lf)
{
    l_daemon_t *ll = (l_daemon_t *) lf->data;
    logfile_buffer_t *b;

    debugs(50, 5, "logfileNewBuffer: " << lf->path << ": new buffer");

    b = static_cast<logfile_buffer_t*>(xcalloc(1, sizeof(logfile_buffer_t)));
    assert(b != NULL);
    b->buf = static_cast<char*>(xcalloc(1, LOGFILE_BUFSZ));
    assert(b->buf != NULL);
    b->size = LOGFILE_BUFSZ;
    b->written_len = 0;
    b->len = 0;
    dlinkAddTail(b, &b->node, &ll->bufs);
    ++ ll->nbufs;
}