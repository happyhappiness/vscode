                          match ? "matched" : "did not match");
        }
        else if (r->content_type) {
            const char **type = provider->types;
            size_t len = strcspn(r->content_type, "; \t");
            AP_DEBUG_ASSERT(type != NULL);
            while (*type) {
                /* Handle 'content-type;charset=...' correctly */
                if (strncmp(*type, r->content_type, len) == 0
                    && (*type)[len] == '\0') {
                    match = 1;
                    break;
                }
                type++;
            }
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Content-Type condition for '%s' %s",
                          provider->frec->name,
                          match ? "matched" : "did not match");
        }

        if (match) {
            /* condition matches this provider */
#ifndef NO_PROTOCOL
            /* check protocol
             *
