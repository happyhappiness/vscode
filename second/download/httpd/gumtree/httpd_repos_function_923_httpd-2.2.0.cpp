static int unserialize_table( cache_header_tbl_t *ctbl,
                              int num_headers,
                              apr_table_t *t )
{
    int i;

    for (i = 0; i < num_headers; ++i) {
        apr_table_addn(t, ctbl[i].hdr, ctbl[i].val);
    }

    return APR_SUCCESS;
}