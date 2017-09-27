        ERR_error_string_n(e, err, sizeof err);
        annotation = ssl_log_annotation(err);

        ap_log_error(file, line, APLOG_MODULE_INDEX, level, 0, s,
                     "SSL Library Error: %s%s%s%s%s%s",
                     /* %s */
                     err, 
                     /* %s%s%s */
                     data ? " (" : "", data ? data : "", data ? ")" : "", 
                     /* %s%s */
                     annotation ? " -- " : "",
                     annotation ? annotation : "");

        /* Pop the error off the stack: */
        ERR_get_error();
    }
}

void ssl_log_cxerror(const char *file, int line, int level, 
                     apr_status_t rv, conn_rec *c, X509 *cert,
                     const char *format, ...)
{
    va_list ap;
    char buf[HUGE_STRING_LEN];
    char *sname, *iname, *serial;
    BIGNUM *bn;
    
    if (APLOG_IS_LEVEL(mySrvFromConn(c),level)) {
        /* Bail early since the rest of this function is expensive. */
        return;
    }

    sname = X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);
    iname = X509_NAME_oneline(X509_get_issuer_name(cert),  NULL, 0);
    bn = ASN1_INTEGER_to_BN(X509_get_serialNumber(cert), NULL);
    serial = bn && !BN_is_zero(bn) ? BN_bn2hex(bn) : NULL;
    
    va_start(ap, format);
    apr_vsnprintf(buf, sizeof buf, format, ap);
    va_end(ap);

    ap_log_cerror(file, line, APLOG_MODULE_INDEX, level, rv, c,
                  "%s [subject: %s, issuer: %s, serial: %s]",
                  buf,
                  sname ? sname : "-unknown-",
                  iname ? iname : "-unknown-",
                  serial ? serial : "-unknown-");

    if (sname) {
        modssl_free(sname);
    }
    
    if (iname) {
        modssl_free(iname);
    }
    
    if (serial) {
        modssl_free(serial);
    }

    if (bn) {
        BN_free(bn);
    }
}
