static int header_do(void *dummy, const char *key, const char *value)
{
    request_rec *r = (request_rec *) dummy;
    const char *payload;

    payload = apr_table_get(r->headers_in, key);
    if (payload) {
        apr_table_setn(r->headers_out, value, payload);
    }

    return 1;
}