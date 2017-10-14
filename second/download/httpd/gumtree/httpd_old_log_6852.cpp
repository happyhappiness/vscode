ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03075)
                      "h2_stream(%ld-%d): submitting push promise fail: %s",
                      session->id, is->id, nghttp2_strerror(nid));