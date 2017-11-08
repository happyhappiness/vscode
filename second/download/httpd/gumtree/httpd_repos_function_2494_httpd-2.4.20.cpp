static h2_sos *h2_sos_h2_status_create(h2_sos *prev) 
{
    h2_sos *sos;
    h2_response *response = prev->response;
    
    apr_table_unset(response->headers, "Content-Length");
    response->content_length = -1;

    sos = apr_pcalloc(prev->stream->pool, sizeof(*sos));
    sos->prev         = prev;
    sos->response     = response;
    sos->stream       = prev->stream;
    sos->buffer       = h2_sos_h2_status_buffer;
    sos->prepare      = h2_sos_h2_status_prepare;
    sos->readx        = h2_sos_h2_status_readx;
    sos->read_to      = h2_sos_h2_status_read_to;
    sos->get_trailers = h2_sos_h2_status_get_trailers;
    
    return sos;
}