static apr_status_t add_h1_trailer(h2_request *req, apr_pool_t *pool, 
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
{
    char *hname, *hvalue;
    
    if (h2_req_ignore_trailer(name, nlen)) {
        return APR_SUCCESS;
    }
    
    hname = apr_pstrndup(pool, name, nlen);
    hvalue = apr_pstrndup(pool, value, vlen);
    h2_util_camel_case_header(hname, nlen);

    apr_table_mergen(req->trailers, hname, hvalue);
    
    return APR_SUCCESS;
}