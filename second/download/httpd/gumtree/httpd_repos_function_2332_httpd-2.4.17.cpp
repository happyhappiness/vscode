apr_status_t h2_to_h1_add_header(h2_to_h1 *to_h1,
                                 const char *name, size_t nlen,
                                 const char *value, size_t vlen)
{
    char *hname, *hvalue;
    if (H2_HD_MATCH_LIT("transfer-encoding", name, nlen)) {
        if (!apr_strnatcasecmp("chunked", value)) {
            /* This should never arrive here in a HTTP/2 request */
            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_BADARG, to_h1->m->c,
                          APLOGNO(02945) 
                          "h2_to_h1: 'transfer-encoding: chunked' received");
            return APR_BADARG;
        }
    }
    else if (H2_HD_MATCH_LIT("content-length", name, nlen)) {
        char *end;
        to_h1->content_len = apr_strtoi64(value, &end, 10);
        if (value == end) {
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, to_h1->m->c,
                          APLOGNO(02959) 
                          "h2_request(%d): content-length value not parsed: %s",
                          to_h1->stream_id, value);
            return APR_EINVAL;
        }
        to_h1->remain_len = to_h1->content_len;
        to_h1->chunked = 0;
    }
    else if (H2_HD_MATCH_LIT("content-type", name, nlen)) {
        /* If we see a content-type and have no length (yet),
         * we need to chunk. */
        to_h1->chunked = (to_h1->content_len == -1);
    }
    else if ((to_h1->seen_host && H2_HD_MATCH_LIT("host", name, nlen))
             || H2_HD_MATCH_LIT("expect", name, nlen)
             || H2_HD_MATCH_LIT("upgrade", name, nlen)
             || H2_HD_MATCH_LIT("connection", name, nlen)
             || H2_HD_MATCH_LIT("proxy-connection", name, nlen)
             || H2_HD_MATCH_LIT("keep-alive", name, nlen)
             || H2_HD_MATCH_LIT("http2-settings", name, nlen)) {
        /* ignore these. */
        return APR_SUCCESS;
    }
    else if (H2_HD_MATCH_LIT("cookie", name, nlen)) {
        const char *existing = apr_table_get(to_h1->headers, "cookie");
        if (existing) {
            char *nval;
            
            /* Cookie headers come separately in HTTP/2, but need
             * to be merged by "; " (instead of default ", ")
             */
            hvalue = apr_pstrndup(to_h1->pool, value, vlen);
            nval = apr_psprintf(to_h1->pool, "%s; %s", existing, hvalue);
            apr_table_setn(to_h1->headers, "Cookie", nval);
            return APR_SUCCESS;
        }
    }
    else if (H2_HD_MATCH_LIT("host", name, nlen)) {
        to_h1->seen_host = 1;
    }
    
    hname = apr_pstrndup(to_h1->pool, name, nlen);
    hvalue = apr_pstrndup(to_h1->pool, value, vlen);
    h2_util_camel_case_header(hname, nlen);
    apr_table_mergen(to_h1->headers, hname, hvalue);
    
    return APR_SUCCESS;
}