static apr_status_t h2_headers_add_h1(apr_table_t *headers, apr_pool_t *pool, 
                                      const char *name, size_t nlen,
                                      const char *value, size_t vlen)
{
    char *hname, *hvalue;
    
    if (h2_proxy_req_ignore_header(name, nlen)) {
        return APR_SUCCESS;
    }
    else if (H2_HD_MATCH_LIT("cookie", name, nlen)) {
        const char *existing = apr_table_get(headers, "cookie");
        if (existing) {
            char *nval;
            
            /* Cookie header come separately in HTTP/2, but need
             * to be merged by "; " (instead of default ", ")
             */
            hvalue = apr_pstrndup(pool, value, vlen);
            nval = apr_psprintf(pool, "%s; %s", existing, hvalue);
            apr_table_setn(headers, "Cookie", nval);
            return APR_SUCCESS;
        }
    }
    else if (H2_HD_MATCH_LIT("host", name, nlen)) {
        if (apr_table_get(headers, "Host")) {
            return APR_SUCCESS; /* ignore duplicate */
        }
    }
    
    hname = apr_pstrndup(pool, name, nlen);
    hvalue = apr_pstrndup(pool, value, vlen);
    h2_proxy_util_camel_case_header(hname, nlen);
    apr_table_mergen(headers, hname, hvalue);
    
    return APR_SUCCESS;
}