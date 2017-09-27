apr_file_printf(stderr_log,
                    "(%d)%s: %s\n",
                    err,
                    apr_strerror(err, errbuf, sizeof(errbuf)),
                    description);