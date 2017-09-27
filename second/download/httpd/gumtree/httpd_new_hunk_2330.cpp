
static char *lookup_map_txtfile(request_rec *r, const char *file, char *key)
{
    apr_file_t *fp = NULL;
    char line[REWRITE_MAX_TXT_MAP_LINE + 1]; /* +1 for \0 */
    char *value, *keylast;
    apr_status_t rv;

    if ((rv = apr_file_open(&fp, file, APR_READ|APR_BUFFERED, APR_OS_DEFAULT,
                            r->pool)) != APR_SUCCESS)
    {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "mod_rewrite: can't open text RewriteMap file %s", file);
        return NULL;
    }

    keylast = key + strlen(key);
    value = NULL;
    while (apr_file_gets(line, sizeof(line), fp) == APR_SUCCESS) {
