static void bucket_destroy(void *data)
{
    h2_bucket_eos *h = data;

    if (apr_bucket_shared_destroy(h)) {
        h2_stream *stream = h->stream;
        if (stream && stream->pool) {
            apr_pool_cleanup_kill(stream->pool, &h->stream, bucket_cleanup);
        }
        apr_bucket_free(h);
        if (stream) {
            h2_stream_eos_destroy(stream);
        }
    }
}