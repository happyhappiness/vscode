        }
    }
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(00094)
                 "Command line: '%s'", result);
}

/* grab bag function to log commonly logged and shared info */
AP_DECLARE(void) ap_log_mpm_common(server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG , 0, s, APLOGNO(02639)
                 "Using SO_REUSEPORT: %s (%d)",
                 ap_have_so_reuseport ? "yes" : "no",
                 ap_num_listen_buckets);
}

AP_DECLARE(void) ap_remove_pid(apr_pool_t *p, const char *rel_fname)
{
    apr_status_t rv;
    const char *fname = ap_server_root_relative(p, rel_fname);

    if (fname != NULL) {
