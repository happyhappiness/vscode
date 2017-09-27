            }

            value += 2;         /* jump over the '..' that we found in the
                                   value */
        }
        else if (directory) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "invalid directory name in map file: %s", r->uri);
            return NULL;
        }

        if (!strncmp(value, "/../", 4) || !strcmp(value, "/..")) {
            value++;            /* step over the '/' if there are more '..'
