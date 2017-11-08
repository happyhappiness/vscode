const h2_priority *h2_stream_get_priority(h2_stream *stream)
{
    h2_response *response = h2_stream_get_response(stream);
    
    if (response && stream->request && stream->request->initiated_on) {
        const char *ctype = apr_table_get(response->headers, "content-type");
        if (ctype) {
            /* FIXME: Not good enough, config needs to come from request->server */
            return h2_config_get_priority(stream->session->config, ctype);
        }
    }
    return NULL;
}