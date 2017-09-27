        return APR_SUCCESS;
    }

    sk = sk_X509_INFO_new_null();

    if (pkp->cert_file) {
        SSL_X509_INFO_load_file(ptemp, sk, pkp->cert_file);
    }

    if (pkp->cert_path) {
        SSL_X509_INFO_load_path(ptemp, sk, pkp->cert_path);
    }

    if ((ncerts = sk_X509_INFO_num(sk)) <= 0) {
        sk_X509_INFO_free(sk);
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02206)
                     "no client certs found for SSL proxy");
