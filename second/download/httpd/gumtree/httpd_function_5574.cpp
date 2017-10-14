static const char *check_macro_arguments(apr_pool_t * pool,
                                         const ap_macro_t * macro)
{
    char **tab = (char **) macro->arguments->elts;
    int nelts = macro->arguments->nelts;
    int i;

    for (i = 0; i < nelts; i++) {
        size_t ltabi = strlen(tab[i]);
        int j;

        if (ltabi == 0) {
            return apr_psprintf(pool,
                                "macro '%s' (%s): empty argument #%d name",
                                macro->name, macro->location, i + 1);
        }
        else if (!looks_like_an_argument(tab[i])) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                         "macro '%s' (%s) "
                         "argument name '%s' (#%d) without expected prefix, "
                         "better prefix argument names with one of '%s'.",
                         macro->name, macro->location,
                         tab[i], i + 1, ARG_PREFIX);
        }

        for (j = i + 1; j < nelts; j++) {
            size_t ltabj = strlen(tab[j]);

            /* must not use the same argument name twice */
            if (!strcmp(tab[i], tab[j])) {
                return apr_psprintf(pool,
                                   "argument name conflict in macro '%s' (%s): "
                                    "argument '%s': #%d and #%d, "
                                    "change argument names!",
                                    macro->name, macro->location,
                                    tab[i], i + 1, j + 1);
            }

            /* warn about common prefix, but only if non empty names */
            if (ltabi && ltabj &&
                !strncmp(tab[i], tab[j], ltabi < ltabj ? ltabi : ltabj)) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING,
                             0, NULL,
                             "macro '%s' (%s): "
                            "argument name prefix conflict (%s #%d and %s #%d),"
                             " be careful about your macro definition!",
                             macro->name, macro->location,
                             tab[i], i + 1, tab[j], j + 1);
            }
        }
    }

    return NULL;
}