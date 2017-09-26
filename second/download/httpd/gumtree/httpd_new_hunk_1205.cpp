        return TRUE;
    }

    if (ssl_verify_error_is_optional(errnum) &&
        (verify == SSL_CVERIFY_OPTIONAL_NO_CA))
    {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, conn,
                      "Certificate Verification: Verifiable Issuer is "
                      "configured as optional, therefore we're accepting "
                      "the certificate");

        sslconn->verify_info = "GENEROUS";
        ok = TRUE;
    }

    /*
