
        modssl_set_cert_info(info, x509, pkey);

        return TRUE;
    }

    for (i = 0; i < sk_X509_NAME_num(ca_list); i++) {
        ca_name = sk_X509_NAME_value(ca_list, i);

        for (j = 0; j < sk_X509_INFO_num(certs); j++) {
            info = sk_X509_INFO_value(certs, j);
            issuer = X509_get_issuer_name(info->x509);

            if (X509_NAME_cmp(issuer, ca_name) == 0) {
                modssl_proxy_info_log(s, info, "found acceptable cert");

                modssl_set_cert_info(info, x509, pkey);

                return TRUE;
            }
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 SSLPROXY_CERT_CB_LOG_FMT
                 "no client certificate found!?", sc->vhost_id);

