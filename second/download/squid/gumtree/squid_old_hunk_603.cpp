    X509 *peeked_cert = (X509 *)SSL_get_ex_data(ssl, ssl_ex_index_ssl_peeked_cert);
    X509 *peer_cert = ctx->cert;

    X509_NAME_oneline(X509_get_subject_name(peer_cert), buffer,
                      sizeof(buffer));

    if (ok) {
        debugs(83, 5, "SSL Certificate signature OK: " << buffer);

        if (server) {
            if (!Ssl::checkX509ServerValidity(peer_cert, server)) {
                debugs(83, 2, "SQUID_X509_V_ERR_DOMAIN_MISMATCH: Certificate " << buffer << " does not match domainname " << server);
                ok = 0;
                error_no = SQUID_X509_V_ERR_DOMAIN_MISMATCH;
            }
        }
