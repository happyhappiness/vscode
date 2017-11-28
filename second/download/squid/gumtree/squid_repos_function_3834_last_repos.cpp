static int
ssl_verify_cb(int ok, X509_STORE_CTX * ctx)
{
    // preserve original ctx->error before SSL_ calls can overwrite it
    Security::ErrorCode error_no = ok ? SSL_ERROR_NONE : X509_STORE_CTX_get_error(ctx);

    char buffer[256] = "";
    SSL *ssl = (SSL *)X509_STORE_CTX_get_ex_data(ctx, SSL_get_ex_data_X509_STORE_CTX_idx());
    SSL_CTX *sslctx = SSL_get_SSL_CTX(ssl);
    SBuf *server = (SBuf *)SSL_get_ex_data(ssl, ssl_ex_index_server);
    void *dont_verify_domain = SSL_CTX_get_ex_data(sslctx, ssl_ctx_ex_index_dont_verify_domain);
    ACLChecklist *check = (ACLChecklist*)SSL_get_ex_data(ssl, ssl_ex_index_cert_error_check);
    X509 *peeked_cert = (X509 *)SSL_get_ex_data(ssl, ssl_ex_index_ssl_peeked_cert);
    Security::CertPointer peer_cert;
    peer_cert.resetAndLock(X509_STORE_CTX_get0_cert(ctx));

    X509_NAME_oneline(X509_get_subject_name(peer_cert.get()), buffer, sizeof(buffer));

    // detect infinite loops
    uint32_t *validationCounter = static_cast<uint32_t *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_validation_counter));
    if (!validationCounter) {
        validationCounter = new uint32_t(1);
        SSL_set_ex_data(ssl, ssl_ex_index_ssl_validation_counter, validationCounter);
    } else {
        // overflows allowed if SQUID_CERT_VALIDATION_ITERATION_MAX >= UINT32_MAX
        (*validationCounter)++;
    }

    if ((*validationCounter) >= SQUID_CERT_VALIDATION_ITERATION_MAX) {
        ok = 0; // or the validation loop will never stop
        error_no = SQUID_X509_V_ERR_INFINITE_VALIDATION;
        debugs(83, 2, "SQUID_X509_V_ERR_INFINITE_VALIDATION: " <<
               *validationCounter << " iterations while checking " << buffer);
    }

    if (ok) {
        debugs(83, 5, "SSL Certificate signature OK: " << buffer);

        // Check for domain mismatch only if the current certificate is the peer certificate.
        if (!dont_verify_domain && server && peer_cert.get() == X509_STORE_CTX_get_current_cert(ctx)) {
            if (!Ssl::checkX509ServerValidity(peer_cert.get(), server->c_str())) {
                debugs(83, 2, "SQUID_X509_V_ERR_DOMAIN_MISMATCH: Certificate " << buffer << " does not match domainname " << server);
                ok = 0;
                error_no = SQUID_X509_V_ERR_DOMAIN_MISMATCH;
            }
        }
    }

    if (ok && peeked_cert) {
        // Check whether the already peeked certificate matches the new one.
        if (X509_cmp(peer_cert.get(), peeked_cert) != 0) {
            debugs(83, 2, "SQUID_X509_V_ERR_CERT_CHANGE: Certificate " << buffer << " does not match peeked certificate");
            ok = 0;
            error_no =  SQUID_X509_V_ERR_CERT_CHANGE;
        }
    }

    if (!ok) {
        Security::CertPointer broken_cert;
        broken_cert.resetAndLock(X509_STORE_CTX_get_current_cert(ctx));
        if (!broken_cert)
            broken_cert = peer_cert;

        Security::CertErrors *errs = static_cast<Security::CertErrors *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_errors));
        const int depth = X509_STORE_CTX_get_error_depth(ctx);
        if (!errs) {
            errs = new Security::CertErrors(Security::CertError(error_no, broken_cert, depth));
            if (!SSL_set_ex_data(ssl, ssl_ex_index_ssl_errors,  (void *)errs)) {
                debugs(83, 2, "Failed to set ssl error_no in ssl_verify_cb: Certificate " << buffer);
                delete errs;
                errs = NULL;
            }
        } else // remember another error number
            errs->push_back_unique(Security::CertError(error_no, broken_cert, depth));

        if (const char *err_descr = Ssl::GetErrorDescr(error_no))
            debugs(83, 5, err_descr << ": " << buffer);
        else
            debugs(83, DBG_IMPORTANT, "SSL unknown certificate error " << error_no << " in " << buffer);

        // Check if the certificate error can be bypassed.
        // Infinity validation loop errors can not bypassed.
        if (error_no != SQUID_X509_V_ERR_INFINITE_VALIDATION) {
            if (check) {
                ACLFilledChecklist *filledCheck = Filled(check);
                assert(!filledCheck->sslErrors);
                filledCheck->sslErrors = new Security::CertErrors(Security::CertError(error_no, broken_cert));
                filledCheck->serverCert = peer_cert;
                if (check->fastCheck().allowed()) {
                    debugs(83, 3, "bypassing SSL error " << error_no << " in " << buffer);
                    ok = 1;
                } else {
                    debugs(83, 5, "confirming SSL error " << error_no);
                }
                delete filledCheck->sslErrors;
                filledCheck->sslErrors = NULL;
                filledCheck->serverCert.reset();
            }
            // If the certificate validator is used then we need to allow all errors and
            // pass them to certficate validator for more processing
            else if (Ssl::TheConfig.ssl_crt_validator) {
                ok = 1;
            }
        }
    }

    if (Ssl::TheConfig.ssl_crt_validator) {
        // Check if we have stored certificates chain. Store if not.
        if (!SSL_get_ex_data(ssl, ssl_ex_index_ssl_cert_chain)) {
            STACK_OF(X509) *certStack = X509_STORE_CTX_get1_chain(ctx);
            if (certStack && !SSL_set_ex_data(ssl, ssl_ex_index_ssl_cert_chain, certStack))
                sk_X509_pop_free(certStack, X509_free);
        }
    }

    if (!ok && !SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail) ) {

        // Find the broken certificate. It may be intermediate.
        Security::CertPointer broken_cert(peer_cert); // reasonable default if search fails
        // Our SQUID_X509_V_ERR_DOMAIN_MISMATCH implies peer_cert is at fault.
        if (error_no != SQUID_X509_V_ERR_DOMAIN_MISMATCH) {
            if (auto *last_used_cert = X509_STORE_CTX_get_current_cert(ctx))
                broken_cert.resetAndLock(last_used_cert);
        }

        auto *errDetail = new Ssl::ErrorDetail(error_no, peer_cert.get(), broken_cert.get());
        if (!SSL_set_ex_data(ssl, ssl_ex_index_ssl_error_detail, errDetail)) {
            debugs(83, 2, "Failed to set Ssl::ErrorDetail in ssl_verify_cb: Certificate " << buffer);
            delete errDetail;
        }
    }

    return ok;
}