bool
configureSslEECDH(SSL_CTX *sslContext, const char *curve)
{
#if OPENSSL_VERSION_NUMBER >= 0x0090800fL && !defined(OPENSSL_NO_ECDH)
    int nid = OBJ_sn2nid(curve);
    if (!nid) {
        debugs(83, DBG_CRITICAL, "ERROR: Unknown EECDH curve '" << curve << "'");
        return false;
    }

    EC_KEY *ecdh = EC_KEY_new_by_curve_name(nid);
    if (ecdh == NULL)
        return false;

    const bool ok = SSL_CTX_set_tmp_ecdh(sslContext, ecdh) != 0;
    EC_KEY_free(ecdh);
    return ok;
#else
    debugs(83, DBG_CRITICAL, "ERROR: EECDH is not available in this build. Please link against OpenSSL>=0.9.8 and ensure OPENSSL_NO_ECDH is not set.");
    return false;
#endif
}