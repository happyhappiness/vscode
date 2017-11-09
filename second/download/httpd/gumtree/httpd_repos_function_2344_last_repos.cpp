apr_status_t h2_res_create_ngtrailer(h2_ngheader **ph, apr_pool_t *p, 
                                    h2_headers *headers)
{
    return ngheader_create(ph, p, is_unsafe(headers), 
                           0, NULL, NULL, headers->headers);
}