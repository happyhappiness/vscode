static h2_sos *h2_sos_mplx_create(h2_stream *stream, h2_response *response)
{
    h2_sos *sos;
    h2_sos_mplx *msos;
    
    msos = apr_pcalloc(stream->pool, sizeof(*msos));
    msos->m = stream->session->mplx;
    msos->bb = apr_brigade_create(stream->pool, msos->m->c->bucket_alloc);
    msos->buffer_size = 32 * 1024;
    
    sos = apr_pcalloc(stream->pool, sizeof(*sos));
    sos->stream = stream;
    sos->response = response;
    
    sos->ctx = msos;
    sos->buffer = h2_sos_mplx_buffer;
    sos->prepare = h2_sos_mplx_prepare;
    sos->readx = h2_sos_mplx_readx;
    sos->read_to = h2_sos_mplx_read_to;
    sos->get_trailers = h2_sos_mplx_get_trailers;
    
    sos->response = response;

    return sos;
}