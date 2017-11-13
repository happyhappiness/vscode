static void ssl_log_cert_error(const char *file, int line, int level,
                               apr_status_t rv, const server_rec *s,
                               const conn_rec *c, const request_rec *r,
                               apr_pool_t *p, X509 *cert, const char *format,
                               va_list ap)
{
    char buf[HUGE_STRING_LEN];
    int msglen, n;
    char *name;

    apr_vsnprintf(buf, sizeof buf, format, ap);

    msglen = strlen(buf);

    if (cert) {
        BIO *bio = BIO_new(BIO_s_mem());

        if (bio) {
            /*
             * Limit the maximum length of the subject and issuer DN strings
             * in the log message. 300 characters should always be sufficient
             * for holding both the timestamp, module name, pid etc. stuff
             * at the beginning of the line and the trailing information about
             * serial, notbefore and notafter.
             */
            int maxdnlen = (HUGE_STRING_LEN - msglen - 300) / 2;

            BIO_puts(bio, " [subject: ");
            name = SSL_X509_NAME_to_string(p, X509_get_subject_name(cert),
                                           maxdnlen);
            if (!strIsEmpty(name)) {
                BIO_puts(bio, name);
            } else {
                BIO_puts(bio, "-empty-");
            }

            BIO_puts(bio, " / issuer: ");
            name = SSL_X509_NAME_to_string(p, X509_get_issuer_name(cert),
                                           maxdnlen);
            if (!strIsEmpty(name)) {
                BIO_puts(bio, name);
            } else {
                BIO_puts(bio, "-empty-");
            }

            BIO_puts(bio, " / serial: ");
            if (i2a_ASN1_INTEGER(bio, X509_get_serialNumber(cert)) == -1)
                BIO_puts(bio, "(ERROR)");

            BIO_puts(bio, " / notbefore: ");
            ASN1_TIME_print(bio, X509_get_notBefore(cert));

            BIO_puts(bio, " / notafter: ");
            ASN1_TIME_print(bio, X509_get_notAfter(cert));

            BIO_puts(bio, "]");

            n = BIO_read(bio, buf + msglen, sizeof buf - msglen - 1);
            if (n > 0)
               buf[msglen + n] = '\0';

            BIO_free(bio);
        }
    }
    else {
        apr_snprintf(buf + msglen, sizeof buf - msglen,
                     " [certificate: -not available-]");
    }

    if (r) {
        ap_log_rerror(file, line, APLOG_MODULE_INDEX, level, rv, r, "%s", buf);
    }
    else if (c) {
        ap_log_cerror(file, line, APLOG_MODULE_INDEX, level, rv, c, "%s", buf);
    }
    else if (s) {
        ap_log_error(file, line, APLOG_MODULE_INDEX, level, rv, s, "%s", buf);
    }

}