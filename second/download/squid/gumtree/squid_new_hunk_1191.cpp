        }
    }

    if (!ok && !SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail) ) {

        // Find the broken certificate. It may be intermediate.
        Security::CertPointer broken_cert(peer_cert); // reasonable default if search fails
        // Our SQUID_X509_V_ERR_DOMAIN_MISMATCH implies peer_cert is at fault.
        if (error_no != SQUID_X509_V_ERR_DOMAIN_MISMATCH) {
            if (auto *last_used_cert = X509_STORE_CTX_get_current_cert(ctx))
                broken_cert.resetAndLock(last_used_cert);
        }

        auto *errDetail = new Ssl::ErrorDetail(error_no, peer_cert.get(), broken_cert.get());
        if (!SSL_set_ex_data(ssl, ssl_ex_index_ssl_error_detail, errDetail)) {
            debugs(83, 2, "Failed to set Ssl::ErrorDetail in ssl_verify_cb: Certificate " << buffer);
            delete errDetail;
        }
    }

    return ok;
}

// "dup" function for SSL_get_ex_new_index("cert_err_check")
#if SQUID_USE_CONST_CRYPTO_EX_DATA_DUP
static int
ssl_dupAclChecklist(CRYPTO_EX_DATA *, const CRYPTO_EX_DATA *, void *,
                    int, long, void *)
#else
static int
ssl_dupAclChecklist(CRYPTO_EX_DATA *, CRYPTO_EX_DATA *, void *,
                    int, long, void *)
#endif
{
    // We do not support duplication of ACLCheckLists.
    // If duplication is needed, we can count copies with cbdata.
    assert(false);
    return 0;
}
