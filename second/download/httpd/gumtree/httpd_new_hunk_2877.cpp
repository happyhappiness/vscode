            return OK;
        }

        /* if we see a bogus header don't ignore it. Shout and scream */

        if (!(l = strchr(w, ':'))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01560)
                "malformed header in meta file: %s", r->filename);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        *l++ = '\0';
        while (*l && apr_isspace(*l))
