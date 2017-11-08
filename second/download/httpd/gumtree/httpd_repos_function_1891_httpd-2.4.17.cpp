static void qs_to_table(const char *input, apr_table_t *parms,
                        apr_pool_t *p)
{
    char *key;
    char *value;
    char *query_string;
    char *strtok_state;

    if (input == NULL) {
        return;
    }

    query_string = apr_pstrdup(p, input);

    key = apr_strtok(query_string, "&", &strtok_state);
    while (key) {
        value = strchr(key, '=');
        if (value) {
            *value = '\0';      /* Split the string in two */
            value++;            /* Skip passed the = */
        }
        else {
            value = "1";
        }
        ap_unescape_url(key);
        ap_unescape_url(value);
        apr_table_set(parms, key, value);
        /*
           ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
           "Found query arg: %s = %s", key, value);
         */
        key = apr_strtok(NULL, "&", &strtok_state);
    }
}