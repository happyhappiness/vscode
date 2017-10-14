ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_from_h1(%d): removed header filter, passing brigade "
                      "len=%ld", from_h1->stream_id, (long)len);