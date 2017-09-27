            *pok = FALSE;
    }
    p++;
    resp_derlen--;
    rsp = d2i_OCSP_RESPONSE(NULL, &p, resp_derlen);
    if (!rsp) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01932)
                     "stapling_get_cached_response: response parse error??");
        return TRUE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01933)
                 "stapling_get_cached_response: cache hit");

    *prsp = rsp;

    return TRUE;
}
