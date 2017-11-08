static int parseargline(char *str, char **a1, char **a2, char **a3)
{
    char quote;

    while (apr_isspace(*str)) {
        ++str;
    }

    /*
     * determine first argument
     */
    quote = (*str == '"' || *str == '\'') ? *str++ : '\0';
    *a1 = str;

    for (; *str; ++str) {
        if ((apr_isspace(*str) && !quote) || (*str == quote)) {
            break;
        }
        if (*str == '\\' && apr_isspace(str[1])) {
            ++str;
            continue;
        }
    }

    if (!*str) {
        return 1;
    }
    *str++ = '\0';

    while (apr_isspace(*str)) {
        ++str;
    }

    /*
     * determine second argument
     */
    quote = (*str == '"' || *str == '\'') ? *str++ : '\0';
    *a2 = str;

    for (; *str; ++str) {
        if ((apr_isspace(*str) && !quote) || (*str == quote)) {
            break;
        }
        if (*str == '\\' && apr_isspace(str[1])) {
            ++str;
            continue;
        }
    }

    if (!*str) {
        *a3 = NULL; /* 3rd argument is optional */
        return 0;
    }
    *str++ = '\0';

    while (apr_isspace(*str)) {
        ++str;
    }

    if (!*str) {
        *a3 = NULL; /* 3rd argument is still optional */
        return 0;
    }

    /*
     * determine third argument
     */
    quote = (*str == '"' || *str == '\'') ? *str++ : '\0';
    *a3 = str;
    for (; *str; ++str) {
        if ((apr_isspace(*str) && !quote) || (*str == quote)) {
            break;
        }
        if (*str == '\\' && apr_isspace(str[1])) {
            ++str;
            continue;
        }
    }
    *str = '\0';

    return 0;
}