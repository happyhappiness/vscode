     * should be suspended. Beware of trailers.
     */
 
    (void)ng2s;
    (void)buf;
    (void)source;
    stream = get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02937) 
                      "h2_stream(%ld-%d): data requested but stream not found",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
