static void bucket_destroy(void *data)
{
    h2_bucket_eos *h = data;

    if (apr_bucket_shared_destroy(h)) {
        h2_stream *stream = h->stream;
        if (stream) {
            h2_stream_cleanup(stream);
        }
        apr_bucket_free(h);
    }
}