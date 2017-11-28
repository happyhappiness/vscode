static void
logfileFreeBuffer(Logfile * lf, logfile_buffer_t * b)
{
    l_daemon_t *ll = (l_daemon_t *) lf->data;
    assert(b != NULL);
    dlinkDelete(&b->node, &ll->bufs);
    -- ll->nbufs;
    xfree(b->buf);
    xfree(b);
}