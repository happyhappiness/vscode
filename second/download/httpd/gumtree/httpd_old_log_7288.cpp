apr_file_printf(stderr_log,
                    "[%s] [client %s] mod_ext_filter (%d)%s: %s\n",
                    time_str,
                    r->useragent_ip,
                    err,
                    apr_strerror(err, errbuf, sizeof(errbuf)),
                    description);