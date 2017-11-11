static char *lookup_map_txtfile(request_rec *r, const char *file, char *key)
{
    apr_file_t *fp = NULL;
    apr_status_t rc;
    char line[1024];
    char *value = NULL;
    char *cpT;
    apr_size_t skip;
    char *curkey;
    char *curval;

    rc = apr_file_open(&fp, file, APR_READ, APR_OS_DEFAULT, r->pool);
    if (rc != APR_SUCCESS) {
       return NULL;
    }

    while (apr_file_gets(line, sizeof(line), fp) == APR_SUCCESS) {
        if (line[0] == '#')
            continue; /* ignore comments */
        cpT = line;
        curkey = cpT;
        skip = strcspn(cpT," \t\r\n");
        if (skip == 0)
            continue; /* ignore lines that start with a space, tab, CR, or LF */
        cpT += skip;
        *cpT = '\0';
        if (strcmp(curkey, key) != 0)
            continue; /* key does not match... */
            
        /* found a matching key; now extract and return the value */
        ++cpT;
        skip = strspn(cpT, " \t\r\n");
        cpT += skip;
        curval = cpT;
        skip = strcspn(cpT, " \t\r\n");
        if (skip == 0)
            continue; /* no value... */
        cpT += skip;
        *cpT = '\0';
        value = apr_pstrdup(r->pool, curval);
        break;
    }
    apr_file_close(fp);
    return value;
}