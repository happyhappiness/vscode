                while (groups[0]) {
                    v = ap_getword(r->pool, &groups, ',');
                    if (!strcmp(v, w))
                        return OK;
                }
            }
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "user %s not in right group: %s",
                          user, r->filename);
            ap_note_basic_auth_failure(r);
            return HTTP_UNAUTHORIZED;
        }
    }
