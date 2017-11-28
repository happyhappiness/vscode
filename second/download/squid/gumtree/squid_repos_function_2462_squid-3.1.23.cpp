static int
ssl_verify_cb(int ok, X509_STORE_CTX * ctx)
{
    char buffer[256];
    SSL *ssl = (SSL *)X509_STORE_CTX_get_ex_data(ctx, SSL_get_ex_data_X509_STORE_CTX_idx());
    SSL_CTX *sslctx = SSL_get_SSL_CTX(ssl);
    const char *server = (const char *)SSL_get_ex_data(ssl, ssl_ex_index_server);
    void *dont_verify_domain = SSL_CTX_get_ex_data(sslctx, ssl_ctx_ex_index_dont_verify_domain);
    ACLChecklist *check = (ACLChecklist*)SSL_get_ex_data(ssl, ssl_ex_index_cert_error_check);
    X509 *peer_cert = ctx->cert;
    Ssl::ssl_error_t error_no = SSL_ERROR_NONE;

    X509_NAME_oneline(X509_get_subject_name(peer_cert), buffer,
                      sizeof(buffer));

    if (ok) {
        debugs(83, 5, "SSL Certificate signature OK: " << buffer);

        if (server) {
            int found = Ssl::matchX509CommonNames(peer_cert, (void *)server, check_domain);

            if (!found) {
                debugs(83, 2, "SQUID_X509_V_ERR_DOMAIN_MISMATCH: Certificate " << buffer << " does not match domainname " << server);
                ok = 0;
                error_no = SQUID_X509_V_ERR_DOMAIN_MISMATCH;

                if (check)
                    Filled(check)->ssl_error = SQUID_X509_V_ERR_DOMAIN_MISMATCH;
            }
        }
    } else {
        error_no = ctx->error;
        switch (ctx->error) {

        case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
        case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
            debugs(83, 5, "SSL Certficate error: CA not known: " << buffer);
            break;

        case X509_V_ERR_CERT_NOT_YET_VALID:
            debugs(83, 5, "SSL Certficate not yet valid: " << buffer);
            break;

        case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
            debugs(83, 5, "SSL Certificate has illegal \'not before\' field: " <<
                   buffer);

            break;

        case X509_V_ERR_CERT_HAS_EXPIRED:
            debugs(83, 5, "SSL Certificate expired: " << buffer);
            break;

        case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
            debugs(83, 5, "SSL Certificate has invalid \'not after\' field: " << buffer);
            break;

        case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            debugs(83, 5, "SSL Certificate is self signed: " << buffer);
            break;

        default:
            debugs(83, 1, "SSL unknown certificate error " << ctx->error << " in " << buffer);
            break;
        }

        if (check)
            Filled(check)->ssl_error = ctx->error;
    }

    if (!ok && check) {
        if (check->fastCheck()) {
            debugs(83, 3, "bypassing SSL error " << ctx->error << " in " << buffer);
            ok = 1;
        } else {
            debugs(83, 5, "confirming SSL error " << ctx->error);
        }
    }

    if (!dont_verify_domain && server) {}

    if (error_no != SSL_ERROR_NONE && !SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail) ) {
        Ssl::ErrorDetail *errDetail = new Ssl::ErrorDetail(error_no, peer_cert);
        if (!SSL_set_ex_data(ssl, ssl_ex_index_ssl_error_detail,  errDetail)) {
            debugs(83, 2, "Failed to set Ssl::ErrorDetail in ssl_verify_cb: Certificate " << buffer);
            delete errDetail;
        }
    }

    return ok;
}