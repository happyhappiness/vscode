                                      const apr_array_header_t * array)
{
    char **tab = (char **) array->elts;
    int i;
    for (i = 0; i < array->nelts; i++) {
        if (empty_string_p(tab[i])) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(02798)
                         "%s: empty argument #%d", where, i + 1);
        }
    }
}

/******************************************************** SUBSTITUTION UTILS */
