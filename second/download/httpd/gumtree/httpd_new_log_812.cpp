apr_psprintf(p, "Could not open configuration file %s: %s",
                            fname, apr_strerror(rv, errmsg, sizeof errmsg));