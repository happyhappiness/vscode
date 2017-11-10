static int filter_header_do(void *v, const char *key, const char *val)
{
    if ((*key == 'W' || *key == 'w') && !strcasecmp(key, "Warning")
            && *val == '1') {
        /* any stored Warning headers with warn-code 1xx (see section
         * 14.46) MUST be deleted from the cache entry and the forwarded
         * response.
         */
    }
    else {
        apr_table_addn(v, key, val);
    }
    return 1;
}