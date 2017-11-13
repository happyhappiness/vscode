h2_stream *h2_stream_create(int id, apr_pool_t *pool, struct h2_mplx *m)
{
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    if (stream != NULL) {
        stream->id = id;
        stream->state = H2_STREAM_ST_IDLE;
        stream->pool = pool;
        stream->m = m;
        stream->request = h2_request_create(id, pool, m->c->bucket_alloc);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                      "h2_stream(%ld-%d): created", m->id, stream->id);
    }
    return stream;
}