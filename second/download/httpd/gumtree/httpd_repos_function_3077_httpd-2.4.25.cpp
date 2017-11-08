static void add_include_vars(request_rec *r)
{
    apr_table_t *e = r->subprocess_env;
    char *t;

    apr_table_setn(e, "DATE_LOCAL", LAZY_VALUE);
    apr_table_setn(e, "DATE_GMT", LAZY_VALUE);
    apr_table_setn(e, "LAST_MODIFIED", LAZY_VALUE);
    apr_table_setn(e, "DOCUMENT_URI", r->uri);
    apr_table_setn(e, "DOCUMENT_ARGS", r->args ? r->args : "");
    if (r->path_info && *r->path_info) {
        apr_table_setn(e, "DOCUMENT_PATH_INFO", r->path_info);
    }
    apr_table_setn(e, "USER_NAME", LAZY_VALUE);
    if (r->filename && (t = strrchr(r->filename, '/'))) {
        apr_table_setn(e, "DOCUMENT_NAME", ++t);
    }
    else {
        apr_table_setn(e, "DOCUMENT_NAME", r->uri);
    }
    if (r->args) {
        char *arg_copy = apr_pstrdup(r->pool, r->args);

        ap_unescape_url(arg_copy);
        apr_table_setn(e, "QUERY_STRING_UNESCAPED",
                  ap_escape_shell_cmd(r->pool, arg_copy));
    }
}