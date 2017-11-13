apr_status_t ap_init_ebcdic(apr_pool_t *pool)
{
    apr_status_t rv;
    char buf[80];

    rv = apr_xlate_open(&ap_hdrs_to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_xlate_open() failed");
        return rv;
    }

    rv = apr_xlate_open(&ap_hdrs_from_ascii, APR_DEFAULT_CHARSET, "ISO8859-1", pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_xlate_open() failed");
        return rv;
    }

    rv = apr_xlate_open(&ap_locale_to_ascii, "ISO8859-1", APR_LOCALE_CHARSET, pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_xlate_open() failed");
        return rv;
    }

    rv = apr_xlate_open(&ap_locale_from_ascii, APR_LOCALE_CHARSET, "ISO8859-1", pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_xlate_open() failed");
        return rv;
    }

    rv = apr_MD5InitEBCDIC(ap_hdrs_to_ascii);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_MD5InitEBCDIC() failed");
        return rv;
    }
    
    rv = apr_base64init_ebcdic(ap_hdrs_to_ascii, ap_hdrs_from_ascii);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_base64init_ebcdic() failed");
        return rv;
    }
    
    rv = apr_SHA1InitEBCDIC(ap_hdrs_to_ascii);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_SHA1InitEBCDIC() failed");
        return rv;
    }
    
    return APR_SUCCESS;
}