static apr_array_header_t *do_languages_line(apr_pool_t *p,
                                             const char **lang_line)
{
    apr_array_header_t *lang_recs = apr_array_make(p, 2, sizeof(char *));

    if (!lang_line) {
        return lang_recs;
    }

    while (**lang_line) {
        char **new = (char **) apr_array_push(lang_recs);
        *new = ap_get_token(p, lang_line, 0);
        ap_str_tolower(*new);
        if (**lang_line == ',' || **lang_line == ';') {
            ++(*lang_line);
        }
    }

    return lang_recs;
}