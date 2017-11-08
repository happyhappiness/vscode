static void h2_stream_cleanup(h2_stream *stream)
{
    if (stream->request) {
        h2_request_destroy(stream->request);
        stream->request = NULL;
    }
}