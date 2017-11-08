apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
                                    apr_bucket_brigade *bb)
{
    stream->response = response;
    if (bb && !APR_BRIGADE_EMPTY(bb)) {
        if (!stream->bbout) {
            stream->bbout = apr_brigade_create(stream->pool, 
                                               stream->m->c->bucket_alloc);
        }
        return h2_util_move(stream->bbout, bb, 16 * 1024, NULL,  
                            "h2_stream_set_response");
    }
    return APR_SUCCESS;
}