static void util_ldap_strdup (char **str, const char *newstr)
{
    if (*str) {
        free(*str);
        *str = NULL;
    }

    if (newstr) {
        *str = calloc(1, strlen(newstr)+1);
        strcpy (*str, newstr);
    }
}