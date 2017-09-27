    expiry += apr_time_now();

    i2d_OCSP_RESPONSE(rsp, &p);

    rv = mc->stapling_cache->store(mc->stapling_cache_context, s,
                                   cinf->idx, sizeof(cinf->idx),
                                   expiry, resp_der, resp_derlen, pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01929)
                     "stapling_cache_response: OCSP response session store error!");
        return FALSE;
    }

