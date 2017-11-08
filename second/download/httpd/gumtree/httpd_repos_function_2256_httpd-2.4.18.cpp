void h2_req_strip_ignored_header(apr_table_t *headers)
{
    int i;
    for (i = 0; i < H2_ALEN(IgnoredRequestHeaders); ++i) {
        apr_table_unset(headers, IgnoredRequestHeaders[i].name);
    }
}