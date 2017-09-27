        }

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
    return(X509_NAME_cmp((void*)*a, (void*)*b));
}
#else
static int ssl_init_FindCAList_X509NameCmp(const X509_NAME * const *a, 
                                           const X509_NAME * const *b)
{
    return(X509_NAME_cmp(*a, *b));
}
#endif

static void ssl_init_PushCAList(STACK_OF(X509_NAME) *ca_list,
                                server_rec *s, const char *file)
{
    int n;
    STACK_OF(X509_NAME) *sk;

    sk = (STACK_OF(X509_NAME) *)
             SSL_load_client_CA_file(MODSSL_PCHAR_CAST file);

    if (!sk) {
        return;
    }

    for (n = 0; n < sk_X509_NAME_num(sk); n++) {
        char name_buf[256];
        X509_NAME *name = sk_X509_NAME_value(sk, n);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "CA certificate: %s",
                     X509_NAME_oneline(name, name_buf, sizeof(name_buf)));

        /*
         * note that SSL_load_client_CA_file() checks for duplicates,
         * but since we call it multiple times when reading a directory
         * we must also check for duplicates ourselves.
         */
