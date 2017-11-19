static void H2_STREAM_OUT_LOG(int lvl, h2_stream *s, char *tag)
{
    if (APLOG_C_IS_LEVEL(s->session->c, lvl)) {
        conn_rec *c = s->session->c;
        char buffer[4 * 1024];
        const char *line = "(null)";
        apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]);
        
        len = h2_util_bb_print(buffer, bmax, tag, "", s->buffer);
        ap_log_cerror(APLOG_MARK, lvl, 0, c, "bb_dump(%ld-%d): %s", 
                      c->id, s->id, len? buffer : line);
    }
}