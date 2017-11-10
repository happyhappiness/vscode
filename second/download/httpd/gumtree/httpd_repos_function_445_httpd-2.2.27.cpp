static void *ap_buffered_log_writer_init(apr_pool_t *p, server_rec *s,
                                        const char* name)
{
    buffered_log *b;
    b = apr_pcalloc(p, sizeof(buffered_log));
    b->handle = ap_default_log_writer_init(p, s, name);

    if (b->handle) {
        *(buffered_log **)apr_array_push(all_buffered_logs) = b;
        return b;
    }
    else
        return NULL;
}