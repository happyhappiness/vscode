        ap_unescape_url(arg_copy);
        apr_table_setn(e, "QUERY_STRING_UNESCAPED",
                       ap_escape_shell_cmd(r->pool, arg_copy));
    }
}

static apr_status_t run_cgi_child(apr_file_t **script_out,
                                  apr_file_t **script_in,
                                  apr_file_t **script_err, 
                                  const char *command,
                                  const char * const argv[],
                                  request_rec *r,
