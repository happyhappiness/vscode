            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                         "%s: could not open error log file %s.",
                         ap_server_argv0, fname);
            exit(1);
        }

        apr_file_set_inherit(s->error_log);
    }
}

void ap_open_logs(server_rec *s_main, apr_pool_t *p)
{
    apr_status_t rc = APR_SUCCESS;
