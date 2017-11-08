static int log_table_entry(const apr_table_t *table, const char *name,
                           char *buf, int buflen)
{
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    const char *value;
    char scratch[MAX_STRING_LEN];

    if ((value = apr_table_get(table, name)) != NULL) {
        ap_escape_errorlog_item(scratch, value, MAX_STRING_LEN);
        return cpystrn(buf, scratch, buflen);
    }

    return 0;
#else
    return cpystrn(buf, apr_table_get(table, name), buflen);
#endif
}