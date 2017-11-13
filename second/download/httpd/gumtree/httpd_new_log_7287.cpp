apr_file_printf(stderr_log,
                    "[%s] [client %s] mod_ext_filter (%d)%pm: %s\n",
                    time_str,
                    r->useragent_ip,
                    err,
                    &err,
                    description);