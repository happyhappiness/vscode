    }
}

static void cgi_child_errfn(apr_pool_t *pool, apr_status_t err,
                            const char *description)
{
    request_rec *r;
    void *vr;

    apr_pool_userdata_get(&vr, ERRFN_USERDATA_KEY, pool);
    r = vr;

    ap_log_rerror(APLOG_MARK, APLOG_ERR, err, r, "%s", description);
}

static apr_status_t run_cgi_child(apr_file_t **script_out,
                                  apr_file_t **script_in,
                                  apr_file_t **script_err, 
                                  const char *command,
