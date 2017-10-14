static void append_scratch(h2_conn_io *io) 
{
    if (io->scratch && io->slen > 0) {
        apr_bucket *b = apr_bucket_heap_create(io->scratch, io->slen,
                                               apr_bucket_free,
                                               io->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
#if LOG_SCRATCH
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03386)
                      "h2_conn_io(%ld): append_scratch(%ld)", 
                      io->c->id, (long)io->slen);
#endif
        io->scratch = NULL;
        io->slen = io->ssize = 0;
    }
}