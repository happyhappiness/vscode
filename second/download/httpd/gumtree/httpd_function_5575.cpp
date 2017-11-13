static const char *check_macro_contents(apr_pool_t * pool,
                                        const ap_macro_t * macro)
{
    int nelts = macro->arguments->nelts;
    char **names = (char **) macro->arguments->elts;
    apr_array_header_t *used;
    int i;
    const char *errmsg;

    if (macro->contents->nelts == 0) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                     "macro '%s' (%s): empty contents!",
                     macro->name, macro->location);
        return NULL;            /* no need to further warnings... */
    }

    used = apr_array_make(pool, nelts, sizeof(char));

    for (i = 0; i < nelts; i++) {
        used->elts[i] = 0;
    }

    errmsg = process_content(pool, macro, macro->arguments, used, NULL);

    if (errmsg) {
        return errmsg;
    }

    for (i = 0; i < nelts; i++) {
        if (!used->elts[i]) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                         "macro '%s' (%s): argument '%s' (#%d) never used",
                         macro->name, macro->location, names[i], i + 1);
        }
    }

    return NULL;
}