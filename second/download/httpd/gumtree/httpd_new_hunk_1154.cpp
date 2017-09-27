    }
    else {
        depth = mctx->auth.verify_depth;
    }

    if (errdepth > depth) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
                      "Certificate Verification: Certificate Chain too long "
                      "(chain has %d certificates, but maximum allowed are "
                      "only %d)",
                      errdepth, depth);

        errnum = X509_V_ERR_CERT_CHAIN_TOO_LONG;
        sslconn->verify_error = X509_verify_cert_error_string(errnum);

        ok = FALSE;
    }
