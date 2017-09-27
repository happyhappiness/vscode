        }

        apr_hash_set(table, key, klen, s);
    }

    if (conflict) {
#ifndef HAVE_TLSEXT
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01917)
                     "Init: You should not use name-based "
                     "virtual hosts in conjunction with SSL!!");
#else
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(02292)
                     "Init: Name-based SSL virtual hosts only "
                     "work for clients with TLS server name indication "
                     "support (RFC 4366)");
#endif
    }

    return APR_SUCCESS;
}

static int ssl_init_FindCAList_X509NameCmp(const X509_NAME * const *a,
                                           const X509_NAME * const *b)
