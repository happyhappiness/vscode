struct h2_response *h2_stream_get_response(h2_stream *stream)
{
    return stream->sos? stream->sos->response : NULL;
}