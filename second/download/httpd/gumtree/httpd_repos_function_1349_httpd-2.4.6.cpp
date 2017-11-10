static int remove_header_do(void *v, const char *key, const char *val)
{
    if ((*key == 'W' || *key == 'w') && !strcasecmp(key, "Warning")) {
        /* any stored Warning headers with warn-code 2xx MUST be retained
         * in the cache entry and the forwarded response.
         */
    }
    else {
        apr_table_unset(v, key);
    }
    return 1;
}