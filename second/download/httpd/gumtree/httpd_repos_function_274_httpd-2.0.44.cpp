time_t dav_get_timeout(request_rec *r)
{
    time_t now, expires = DAV_TIMEOUT_INFINITE;

    const char *timeout_const = apr_table_get(r->headers_in, "Timeout");
    const char *timeout = apr_pstrdup(r->pool, timeout_const), *val;

    if (timeout == NULL)
        return DAV_TIMEOUT_INFINITE;

    /* Use the first thing we understand, or infinity if
     * we don't understand anything.
     */

    while ((val = ap_getword_white(r->pool, &timeout)) && strlen(val)) {
        if (!strncmp(val, "Infinite", 8)) {
            return DAV_TIMEOUT_INFINITE;
        }

        if (!strncmp(val, "Second-", 7)) {
            val += 7;
            /* ### We need to handle overflow better:
             * ### timeout will be <= 2^32 - 1
             */
            expires = atol(val);
            now     = time(NULL);
            return now + expires;
        }
    }

    return DAV_TIMEOUT_INFINITE;
}