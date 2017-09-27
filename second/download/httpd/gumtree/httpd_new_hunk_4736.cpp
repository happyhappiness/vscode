                          match ? "matched" : "did not match");
        }
        else if (r->content_type) {
            const char **type = provider->types;
            size_t len = strcspn(r->content_type, "; \t");
            AP_DEBUG_ASSERT(type != NULL);
            ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                          "Content-Type '%s' ...", r->content_type);
            while (*type) {
                /* Handle 'content-type;charset=...' correctly */
                if (strncmp(*type, r->content_type, len) == 0
                    && (*type)[len] == '\0') {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                                  "... matched '%s'", *type);
                    match = 1;
                    break;
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                                  "... did not match '%s'", *type);
                }
                type++;
            }
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Content-Type condition for '%s' %s",
                          provider->frec->name,
                          match ? "matched" : "did not match");
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Content-Type condition for '%s' did not match: "
                          "no Content-Type", provider->frec->name);
        }

        if (match) {
            /* condition matches this provider */
#ifndef NO_PROTOCOL
            /* check protocol
             *
