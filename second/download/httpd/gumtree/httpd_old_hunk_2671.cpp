    r = vr;
    apr_file_open_stderr(&stderr_log, pool);
    ap_recent_ctime(time_str, apr_time_now());
    apr_file_printf(stderr_log,
                    "[%s] [client %s] mod_ext_filter (%d)%s: %s\n",
                    time_str,
                    r->connection->remote_ip,
                    err,
                    apr_strerror(err, errbuf, sizeof(errbuf)),
                    description);
}

/* init_ext_filter_process: get the external filter process going
