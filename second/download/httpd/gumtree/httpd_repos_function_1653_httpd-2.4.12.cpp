static const char *substitute_macro_args(
    char *buf,
    int bufsize,
    const ap_macro_t * macro,
    const apr_array_header_t * replacements,
    apr_array_header_t * used)
{
    char *ptr = buf,
        **atab = (char **) macro->arguments->elts,
        **rtab = (char **) replacements->elts;
    int whichone = -1;

    if (used) {
        ap_assert(used->nalloc >= replacements->nelts);
    }
    debug(fprintf(stderr, "1# %s", buf));

    while ((ptr = next_substitution(ptr, macro->arguments, &whichone))) {
        const char *errmsg = substitute(ptr, buf - ptr + bufsize,
                                        atab[whichone], rtab[whichone],
                                        atab[whichone][0] == ESCAPE_ARG);
        if (errmsg) {
            return errmsg;
        }
        ptr += strlen(rtab[whichone]);
        if (used) {
            used->elts[whichone] = 1;
        }
    }
    debug(fprintf(stderr, "2# %s", buf));

    return NULL;
}