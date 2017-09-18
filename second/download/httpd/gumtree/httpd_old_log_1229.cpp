fprintf(stderr, "%s: could not open config directory %s: %s\n",
                    ap_server_argv0, fname,
                    apr_strerror(rv, errmsg, sizeof errmsg));