        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server,
                     "Init: You should not use name-based "
                     "virtual hosts in conjunction with SSL!!");
    }
}

static int ssl_init_FindCAList_X509NameCmp(X509_NAME **a, X509_NAME **b)
{
    return(X509_NAME_cmp(*a, *b));
}

static void ssl_init_PushCAList(STACK_OF(X509_NAME) *ca_list,
                                server_rec *s, const char *file)
{
    int n;
    STACK_OF(X509_NAME) *sk;

    sk = (STACK_OF(X509_NAME) *)SSL_load_client_CA_file(file);

    if (!sk) {
        return;
    }

    for (n = 0; n < sk_X509_NAME_num(sk); n++) {
