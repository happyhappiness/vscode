                     "could not create %s", fname);
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "%s: could not log pid to file %s",
                     ap_server_argv0, fname);
        exit(1);
    }
    apr_file_printf(pid_file, "%ld" APR_EOL_STR, (long)mypid);
    apr_file_close(pid_file);
    saved_pid = mypid;
}

AP_DECLARE(apr_status_t) ap_read_pid(apr_pool_t *p, const char *filename,
                                     pid_t *mypid)
