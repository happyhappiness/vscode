        }
    }
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(00094)
                 "Command line: '%s'", result);
}

AP_DECLARE(void) ap_remove_pid(apr_pool_t *p, const char *rel_fname)
{
    apr_status_t rv;
    const char *fname = ap_server_root_relative(p, rel_fname);

    if (fname != NULL) {
