h2_ngheader *h2_util_ngheader_make(apr_pool_t *p, apr_table_t *header)
{
    h2_ngheader *ngh;
    size_t n;
    
    n = 0;
    apr_table_do(count_header, &n, header, NULL);
    
    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    apr_table_do(add_table_header, ngh, header, NULL);

    return ngh;
}