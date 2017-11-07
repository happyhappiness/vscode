ap_log_cerror(APLOG_MARK, GCSLOG_LEVEL, 0, session->c,
                              "push_diary_update: already there PUSH %s", push->req->path);