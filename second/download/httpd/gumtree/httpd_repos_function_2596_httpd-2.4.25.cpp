static int log_header(void *ctx, const char *key, const char *value)
{
    h2_proxy_stream *stream = ctx;
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, stream->r, 
                  "h2_proxy_stream(%s-%d), header_out %s: %s", 
                  stream->session->id, stream->id, key, value);
    return 1;
}