    x = SSL_get_certificate(ssl);
    if (x == NULL)
        return NULL;
    cinf = X509_get_ex_data(x, stapling_ex_idx);
    if (cinf && cinf->cid)
        return cinf;
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "stapling_get_cert_info: stapling not supported for certificate");
    return NULL;
}

/*
 * OCSP response caching code. The response is preceded by a flag value
