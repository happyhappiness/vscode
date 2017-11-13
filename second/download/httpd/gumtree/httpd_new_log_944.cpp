apr_psprintf(p, "Could not open config directory %s: %s",
                                path, apr_strerror(rv, errmsg, sizeof errmsg));