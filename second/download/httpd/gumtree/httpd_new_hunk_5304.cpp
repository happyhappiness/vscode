        }

        apr_hash_set(table, key, klen, s);
    }

    if (conflict) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01917)
                     "Init: Name-based SSL virtual hosts require "
                     "an OpenSSL version with support for TLS extensions "
                     "(RFC 6066 - Server Name Indication / SNI), "
                     "but the currently used library version (%s) is "
                     "lacking this feature", SSLeay_version(SSLEAY_VERSION));
    }
#endif

    return APR_SUCCESS;
}

static int ssl_init_FindCAList_X509NameCmp(const X509_NAME * const *a,
                                           const X509_NAME * const *b)
