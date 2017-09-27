{
    int override_list_ok = 0;
    char *w, *w2, *w3;
    const char *errmsg = NULL;

    /** Have we been provided a list of acceptable directives? */
    if (parms->override_list != NULL) { 
         if (apr_table_get(parms->override_list, cmd->name) != NULL) { 
              override_list_ok = 1;
         }
    }

    if ((parms->override & cmd->req_override) == 0 && !override_list_ok) {
        if (parms->override & NONFATAL_OVERRIDE) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, parms->temp_pool,
                          APLOGNO(02295)
                          "%s in .htaccess forbidden by AllowOverride",
