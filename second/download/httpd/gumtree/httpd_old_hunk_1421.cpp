            X509_REVOKED *revoked =
                sk_X509_REVOKED_value(X509_CRL_get_REVOKED(crl), i);

            ASN1_INTEGER *sn = X509_REVOKED_get_serialNumber(revoked);

            if (!ASN1_INTEGER_cmp(sn, X509_get_serialNumber(cert))) {
                if (s->loglevel >= APLOG_DEBUG) {
                    char *cp = X509_NAME_oneline(issuer, NULL, 0);
                    long serial = ASN1_INTEGER_get(sn);

                    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                                 "Certificate with serial %ld (0x%lX) "
                                 "revoked per CRL from issuer %s",
