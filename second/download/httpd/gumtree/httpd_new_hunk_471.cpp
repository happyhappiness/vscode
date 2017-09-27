            BIO_printf(bio, ", lastUpdate: ");
            ASN1_UTCTIME_print(bio, X509_CRL_get_lastUpdate(crl));

            BIO_printf(bio, ", nextUpdate: ");
            ASN1_UTCTIME_print(bio, X509_CRL_get_nextUpdate(crl));

            n = BIO_read(bio, buff, sizeof(buff) - 1);
            buff[n] = '\0';

            BIO_free(bio);

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, buff);
        }
