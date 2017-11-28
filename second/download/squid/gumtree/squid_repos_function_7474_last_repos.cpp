void
Security::PeerOptions::updateContextCrl(Security::ContextPointer &ctx)
{
#if USE_OPENSSL
    bool verifyCrl = false;
    X509_STORE *st = SSL_CTX_get_cert_store(ctx.get());
    if (parsedCrl.size()) {
        for (auto &i : parsedCrl) {
            if (!X509_STORE_add_crl(st, i.get()))
                debugs(83, 2, "WARNING: Failed to add CRL");
            else
                verifyCrl = true;
        }
    }

#if X509_V_FLAG_CRL_CHECK
    if ((parsedFlags & SSL_FLAG_VERIFY_CRL_ALL))
        X509_STORE_set_flags(st, X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
    else if (verifyCrl || (parsedFlags & SSL_FLAG_VERIFY_CRL))
        X509_STORE_set_flags(st, X509_V_FLAG_CRL_CHECK);
#endif

#endif /* USE_OPENSSL */
}