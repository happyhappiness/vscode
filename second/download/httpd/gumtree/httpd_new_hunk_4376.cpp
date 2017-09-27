    }
    
    if (!h2_proxy_res_ignore_header(n, nlen)) {
        char *hname, *hvalue;
    
        hname = apr_pstrndup(stream->pool, n, nlen);
        h2_proxy_util_camel_case_header(hname, nlen);
        hvalue = apr_pstrndup(stream->pool, v, vlen);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                      "h2_proxy_stream(%s-%d): got header %s: %s", 
                      stream->session->id, stream->id, hname, hvalue);
        process_proxy_header(stream, hname, hvalue);
    }
    return APR_SUCCESS;
}

static int log_header(void *ctx, const char *key, const char *value)
{
