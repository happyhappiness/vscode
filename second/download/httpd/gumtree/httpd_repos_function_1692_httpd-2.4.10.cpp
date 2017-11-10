static int handle_autoindex(request_rec *r)
{
    autoindex_config_rec *d;
    int allow_opts;

    if(strcmp(r->handler,DIR_MAGIC_TYPE)) {
        return DECLINED;
    }

    allow_opts = ap_allow_options(r);

    d = (autoindex_config_rec *) ap_get_module_config(r->per_dir_config,
                                                      &autoindex_module);

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    /* OK, nothing easy.  Trot out the heavy artillery... */

    if (allow_opts & OPT_INDEXES) {
        int errstatus;

        if ((errstatus = ap_discard_request_body(r)) != OK) {
            return errstatus;
        }

        /* KLUDGE --- make the sub_req lookups happen in the right directory.
         * Fixing this in the sub_req_lookup functions themselves is difficult,
         * and would probably break virtual includes...
         */

        if (r->filename[strlen(r->filename) - 1] != '/') {
            r->filename = apr_pstrcat(r->pool, r->filename, "/", NULL);
        }
        return index_directory(r, d);
    }
    else {
        const char *index_names = apr_table_get(r->notes, "dir-index-names");

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01276)
                      "Cannot serve directory %s: No matching DirectoryIndex (%s) found, and "
                      "server-generated directory index forbidden by "
                      "Options directive",
                       r->filename,
                       index_names ? index_names : "none");
        return HTTP_FORBIDDEN;
    }
}