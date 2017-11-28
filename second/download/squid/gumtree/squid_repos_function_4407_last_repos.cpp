static wchar_t **
build_groups_DN_array(const char **array, char *userdomain)
{
    wchar_t *wc = NULL;
    int wcsize;
    int source_group_format;
    char Group[GNLEN + 1];

    wchar_t **wc_array, **entry;

    entry = wc_array = (wchar_t **) xmalloc((numberofgroups + 1) * sizeof(wchar_t *));

    while (*array) {
        if (strchr(*array, '/') != NULL) {
            strncpy(Group, *array, GNLEN);
            source_group_format = ADS_NAME_TYPE_CANONICAL;
        } else {
            source_group_format = ADS_NAME_TYPE_NT4;
            if (strchr(*array, '\\') == NULL) {
                strcpy(Group, userdomain);
                strcat(Group, "\\");
                strncat(Group, *array, GNLEN - sizeof(userdomain) - 1);
            } else
                strncpy(Group, *array, GNLEN);
        }

        wcsize = MultiByteToWideChar(CP_ACP, 0, Group, -1, wc, 0);
        wc = (wchar_t *) xmalloc(wcsize * sizeof(wchar_t));
        MultiByteToWideChar(CP_ACP, 0, Group, -1, wc, wcsize);
        *entry = My_NameTranslate(wc, source_group_format, ADS_NAME_TYPE_1779);
        safe_free(wc);
        ++array;
        if (*entry == NULL) {
            debug("build_groups_DN_array: cannot get DN for '%s'.\n", Group);
            continue;
        }
        ++entry;
    }
    *entry = NULL;
    return wc_array;
}