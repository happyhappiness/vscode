static const char *process_content(apr_pool_t * pool,
                                   const ap_macro_t * macro,
                                   const apr_array_header_t * replacements,
                                   apr_array_header_t * used,
                                   apr_array_header_t ** result)
{
    apr_array_header_t *contents = macro->contents;
    char line[MAX_STRING_LEN];
    int i;

    if (result) {
        *result = apr_array_make(pool, 1, sizeof(char *));
    }

    /* for each line of the macro body */
    for (i = 0; i < contents->nelts; i++) {
        const char *errmsg;
        /* copy the line and subtitute macro parameters */
        strncpy(line, ((char **) contents->elts)[i], MAX_STRING_LEN - 1);
        errmsg = substitute_macro_args(line, MAX_STRING_LEN,
                                       macro, replacements, used);
        if (errmsg) {
            return apr_psprintf(pool,
                               "while processing line %d of macro '%s' (%s) %s",
                                i + 1, macro->name, macro->location, errmsg);
        }
        /* append substituted line to result array */
        if (result) {
            char **new = apr_array_push(*result);
            *new = apr_pstrdup(pool, line);
        }
    }

    return NULL;
}