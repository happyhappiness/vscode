void h2_stream_set_h2_request(h2_stream *stream, int initiated_on,
                              const h2_request *req)
{
    h2_request_copy(stream->pool, stream->request, req);
    stream->initiated_on = initiated_on;
    stream->request->eoh = 0;
}