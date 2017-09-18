        return TRUE;
    }

    if (ssl_verify_error_is_optional(errnum) &&
        (verify == SSL_CVERIFY_OPTIONAL_NO_CA))
    {
        ssl_log(s, SSL_LOG_TRACE,
                "Certificate Verification: Verifiable Issuer is configured as "
                "optional, therefore we're accepting the certificate");

        sslconn->verify_info = "GENEROUS";
        ok = TRUE;
    }

    /*
