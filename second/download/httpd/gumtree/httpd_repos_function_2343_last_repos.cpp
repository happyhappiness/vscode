static int is_unsafe(h2_headers *h)
{
    const char *v = apr_table_get(h->notes, H2_HDR_CONFORMANCE);
    return (v && !strcmp(v, H2_HDR_CONFORMANCE_UNSAFE));
}