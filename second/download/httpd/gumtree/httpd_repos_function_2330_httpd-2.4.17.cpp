h2_to_h1 *h2_to_h1_create(int stream_id, apr_pool_t *pool, 
                          apr_bucket_alloc_t *bucket_alloc, 
                          const char *method, 
                          const char *scheme, 
                          const char *authority, 
                          const char *path,
                          struct h2_mplx *m)
{
    h2_to_h1 *to_h1;
    if (!method) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, m->c,
                      APLOGNO(02943) 
                      "h2_to_h1: header start but :method missing");
        return NULL;
    }
    if (!path) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, m->c,
                      APLOGNO(02944) 
                      "h2_to_h1: header start but :path missing");
        return NULL;
    }
    
    to_h1 = apr_pcalloc(pool, sizeof(h2_to_h1));
    if (to_h1) {
        to_h1->stream_id = stream_id;
        to_h1->pool = pool;
        to_h1->method = method;
        to_h1->scheme = scheme;
        to_h1->authority = authority;
        to_h1->path = path;
        to_h1->m = m;
        to_h1->headers = apr_table_make(to_h1->pool, 10);
        to_h1->bb = apr_brigade_create(pool, bucket_alloc);
        to_h1->chunked = 0; /* until we see a content-type and no length */
        to_h1->content_len = -1;
    }
    return to_h1;
}