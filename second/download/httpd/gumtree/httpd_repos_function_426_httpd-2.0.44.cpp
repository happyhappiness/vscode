static void *ap_buffered_log_writer_init(apr_pool_t *p, server_rec *s, 
                                        const char* name)
{
    buffered_log *b;
    b = apr_palloc(p, sizeof(buffered_log));
    b->handle = ap_default_log_writer_init(p, s, name);
    b->outcnt = 0;
    
    if (b->handle)
        return b;
    else
        return NULL;
}