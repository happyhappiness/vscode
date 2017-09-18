        ap_unescape_url(arg_copy);
        apr_table_setn(e, "QUERY_STRING_UNESCAPED",
                       ap_escape_shell_cmd(r->pool, arg_copy));
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
                                  const char * const argv[],
                                  request_rec *r,
