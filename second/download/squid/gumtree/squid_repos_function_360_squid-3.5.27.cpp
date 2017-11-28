char *
escape_filter(char *filter)
{
    char *ldap_filter_esc, *ldf;
    size_t i;

    i = 0;
    for (ldap_filter_esc = filter; *ldap_filter_esc; ++ldap_filter_esc) {
        if ((*ldap_filter_esc == '*') ||
                (*ldap_filter_esc == '(') ||
                (*ldap_filter_esc == ')') ||
                (*ldap_filter_esc == '\\'))
            i = i + 3;
    }

    ldap_filter_esc = (char *) xcalloc(strlen(filter) + i + 1, sizeof(char));
    ldf = ldap_filter_esc;
    for (; *filter; ++filter) {
        if (*filter == '*') {
            strcpy(ldf, "\\2a");
            ldf = ldf + 3;
        } else if (*filter == '(') {
            strcpy(ldf, "\\28");
            ldf = ldf + 3;
        } else if (*filter == ')') {
            strcpy(ldf, "\\29");
            ldf = ldf + 3;
        } else if (*filter == '\\') {
            strcpy(ldf, "\\5c");
            ldf = ldf + 3;
        } else {
            *ldf = *filter;
            ++ldf;
        }
    }
    *ldf = '\0';

    return ldap_filter_esc;
}