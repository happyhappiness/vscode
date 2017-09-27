                                          mctx->auth.ca_cert_file,
                                          mctx->auth.ca_cert_path);
        if (sk_X509_NAME_num(ca_list) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01896)
                    "Unable to determine list of acceptable "
                    "CA certificates for client authentication");
            return ssl_die(s);
        }

        SSL_CTX_set_client_CA_list(ctx, ca_list);
    }

    /*
