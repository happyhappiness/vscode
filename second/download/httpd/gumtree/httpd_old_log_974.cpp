fprintf(stderr, "%s: could not open config directory %s: %s\n",
                    ap_server_argv0, path,
                    apr_strerror(rv, errmsg, sizeof errmsg));