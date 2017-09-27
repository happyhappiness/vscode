
        apr_hash_set(table, key, klen, s);
    }

    if (conflict) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server,
#ifdef OPENSSL_NO_TLSEXT
                     "Init: You should not use name-based "
                     "virtual hosts in conjunction with SSL!!");
#else
                     "Init: Name-based SSL virtual hosts only "
                     "work for clients with TLS server name indication "
                     "support (RFC 4366)");
#endif
    }
}

#ifdef SSLC_VERSION_NUMBER
static int ssl_init_FindCAList_X509NameCmp(char **a, char **b)
{
