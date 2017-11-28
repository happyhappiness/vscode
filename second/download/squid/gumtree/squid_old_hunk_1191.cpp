        }
    }

    if (!ok && !SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail) ) {

        // Find the broken certificate. It may be intermediate.
        X509 *broken_cert = peer_cert; // reasonable default if search fails
        // Our SQUID_X509_V_ERR_DOMAIN_MISMATCH implies peer_cert is at fault.
        if (error_no != SQUID_X509_V_ERR_DOMAIN_MISMATCH) {
            if (X509 *last_used_cert = X509_STORE_CTX_get_current_cert(ctx))
                broken_cert = last_used_cert;
        }

        Ssl::ErrorDetail *errDetail =
            new Ssl::ErrorDetail(error_no, peer_cert, broken_cert);

        if (!SSL_set_ex_data(ssl, ssl_ex_index_ssl_error_detail,  errDetail)) {
            debugs(83, 2, "Failed to set Ssl::ErrorDetail in ssl_verify_cb: Certificate " << buffer);
            delete errDetail;
        }
    }

    return ok;
}

/// \ingroup ServerProtocolSSLInternal
static struct ssl_option {
    const char *name;
    long value;
}

ssl_options[] = {

#if SSL_OP_MICROSOFT_SESS_ID_BUG
    {
        "MICROSOFT_SESS_ID_BUG", SSL_OP_MICROSOFT_SESS_ID_BUG
    },
#endif
#if SSL_OP_NETSCAPE_CHALLENGE_BUG
    {
        "NETSCAPE_CHALLENGE_BUG", SSL_OP_NETSCAPE_CHALLENGE_BUG
    },
#endif
#if SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG
    {
        "NETSCAPE_REUSE_CIPHER_CHANGE_BUG", SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG
    },
#endif
#if SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG
    {
        "SSLREF2_REUSE_CERT_TYPE_BUG", SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG
    },
#endif
#if SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER
    {
        "MICROSOFT_BIG_SSLV3_BUFFER", SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER
    },
#endif
#if SSL_OP_MSIE_SSLV2_RSA_PADDING
    {
        "MSIE_SSLV2_RSA_PADDING", SSL_OP_MSIE_SSLV2_RSA_PADDING
    },
#endif
#if SSL_OP_SSLEAY_080_CLIENT_DH_BUG
    {
        "SSLEAY_080_CLIENT_DH_BUG", SSL_OP_SSLEAY_080_CLIENT_DH_BUG
    },
#endif
#if SSL_OP_TLS_D5_BUG
    {
        "TLS_D5_BUG", SSL_OP_TLS_D5_BUG
    },
#endif
#if SSL_OP_TLS_BLOCK_PADDING_BUG
    {
        "TLS_BLOCK_PADDING_BUG", SSL_OP_TLS_BLOCK_PADDING_BUG
    },
#endif
#if SSL_OP_TLS_ROLLBACK_BUG
    {
        "TLS_ROLLBACK_BUG", SSL_OP_TLS_ROLLBACK_BUG
    },
#endif
#if SSL_OP_ALL
    {
        "ALL", (long)SSL_OP_ALL
    },
#endif
#if SSL_OP_SINGLE_DH_USE
    {
        "SINGLE_DH_USE", SSL_OP_SINGLE_DH_USE
    },
#endif
#if SSL_OP_EPHEMERAL_RSA
    {
        "EPHEMERAL_RSA", SSL_OP_EPHEMERAL_RSA
    },
#endif
#if SSL_OP_PKCS1_CHECK_1
    {
        "PKCS1_CHECK_1", SSL_OP_PKCS1_CHECK_1
    },
#endif
#if SSL_OP_PKCS1_CHECK_2
    {
        "PKCS1_CHECK_2", SSL_OP_PKCS1_CHECK_2
    },
#endif
#if SSL_OP_NETSCAPE_CA_DN_BUG
    {
        "NETSCAPE_CA_DN_BUG", SSL_OP_NETSCAPE_CA_DN_BUG
    },
#endif
#if SSL_OP_NON_EXPORT_FIRST
    {
        "NON_EXPORT_FIRST", SSL_OP_NON_EXPORT_FIRST
    },
#endif
#if SSL_OP_CIPHER_SERVER_PREFERENCE
    {
        "CIPHER_SERVER_PREFERENCE", SSL_OP_CIPHER_SERVER_PREFERENCE
    },
#endif
#if SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG
    {
        "NETSCAPE_DEMO_CIPHER_CHANGE_BUG", SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG
    },
#endif
#if SSL_OP_NO_SSLv2
    {
        "NO_SSLv2", SSL_OP_NO_SSLv2
    },
#endif
#if SSL_OP_NO_SSLv3
    {
        "NO_SSLv3", SSL_OP_NO_SSLv3
    },
#endif
#if SSL_OP_NO_TLSv1
    {
        "NO_TLSv1", SSL_OP_NO_TLSv1
    },
#endif
#if SSL_OP_NO_TLSv1_1
    {
        "NO_TLSv1_1", SSL_OP_NO_TLSv1_1
    },
#endif
#if SSL_OP_NO_TLSv1_2
    {
        "NO_TLSv1_2", SSL_OP_NO_TLSv1_2
    },
#endif
#if SSL_OP_NO_COMPRESSION
    {
        "No_Compression", SSL_OP_NO_COMPRESSION
    },
#endif
#if SSL_OP_NO_TICKET
    {
        "NO_TICKET", SSL_OP_NO_TICKET
    },
#endif
#if SSL_OP_SINGLE_ECDH_USE
    {
        "SINGLE_ECDH_USE", SSL_OP_SINGLE_ECDH_USE
    },
#endif
    {
        "", 0
    },
    {
        NULL, 0
    }
};

/// \ingroup ServerProtocolSSLInternal
long
Ssl::parse_options(const char *options)
{
    long op = 0;
    char *tmp;
    char *option;

    if (!options)
        goto no_options;

    tmp = xstrdup(options);

    option = strtok(tmp, ":,");

    while (option) {

        struct ssl_option *opt = NULL, *opttmp;
        long value = 0;
        enum {
            MODE_ADD, MODE_REMOVE
        } mode;

        switch (*option) {

        case '!':

        case '-':
            mode = MODE_REMOVE;
            ++option;
            break;

        case '+':
            mode = MODE_ADD;
            ++option;
            break;

        default:
            mode = MODE_ADD;
            break;
        }

        for (opttmp = ssl_options; opttmp->name; ++opttmp) {
            if (strcmp(opttmp->name, option) == 0) {
                opt = opttmp;
                break;
            }
        }

        if (opt)
            value = opt->value;
        else if (strncmp(option, "0x", 2) == 0) {
            /* Special case.. hex specification */
            value = strtol(option + 2, NULL, 16);
        } else {
            fatalf("Unknown SSL option '%s'", option);
            value = 0;      /* Keep GCC happy */
        }

        switch (mode) {

        case MODE_ADD:
            op |= value;
            break;

        case MODE_REMOVE:
            op &= ~value;
            break;
        }

        option = strtok(NULL, ":,");
    }

    safe_free(tmp);

no_options:
    return op;
}

/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_NO_DEFAULT_CA      (1<<0)
/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_DELAYED_AUTH       (1<<1)
/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_DONT_VERIFY_PEER   (1<<2)
/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_DONT_VERIFY_DOMAIN (1<<3)
/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_NO_SESSION_REUSE   (1<<4)
/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_VERIFY_CRL     (1<<5)
/// \ingroup ServerProtocolSSLInternal
#define SSL_FLAG_VERIFY_CRL_ALL     (1<<6)

/// \ingroup ServerProtocolSSLInternal
long
Ssl::parse_flags(const char *flags)
{
    long fl = 0;
    char *tmp;
    char *flag;

    if (!flags)
        return 0;

    tmp = xstrdup(flags);

    flag = strtok(tmp, ":,");

    while (flag) {
        if (strcmp(flag, "NO_DEFAULT_CA") == 0)
            fl |= SSL_FLAG_NO_DEFAULT_CA;
        else if (strcmp(flag, "DELAYED_AUTH") == 0)
            fl |= SSL_FLAG_DELAYED_AUTH;
        else if (strcmp(flag, "DONT_VERIFY_PEER") == 0)
            fl |= SSL_FLAG_DONT_VERIFY_PEER;
        else if (strcmp(flag, "DONT_VERIFY_DOMAIN") == 0)
            fl |= SSL_FLAG_DONT_VERIFY_DOMAIN;
        else if (strcmp(flag, "NO_SESSION_REUSE") == 0)
            fl |= SSL_FLAG_NO_SESSION_REUSE;

#if X509_V_FLAG_CRL_CHECK

        else if (strcmp(flag, "VERIFY_CRL") == 0)
            fl |= SSL_FLAG_VERIFY_CRL;
        else if (strcmp(flag, "VERIFY_CRL_ALL") == 0)
            fl |= SSL_FLAG_VERIFY_CRL_ALL;

#endif

        else
            fatalf("Unknown ssl flag '%s'", flag);

        flag = strtok(NULL, ":,");
    }

    safe_free(tmp);
    return fl;
}

// "dup" function for SSL_get_ex_new_index("cert_err_check")
static int
ssl_dupAclChecklist(CRYPTO_EX_DATA *, CRYPTO_EX_DATA *, void *,
                    int, long, void *)
{
    // We do not support duplication of ACLCheckLists.
    // If duplication is needed, we can count copies with cbdata.
    assert(false);
    return 0;
}
