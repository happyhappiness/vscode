        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(02292)
                     "Init: Name-based SSL virtual hosts only "
                     "work for clients with TLS server name indication "
                     "support (RFC 4366)");
#endif
    }
}

static int ssl_init_FindCAList_X509NameCmp(const X509_NAME * const *a,
                                           const X509_NAME * const *b)
{
    return(X509_NAME_cmp(*a, *b));
