void
Security::ServerOptions::updateContextEecdh(Security::ContextPointer &ctx)
{
    // set Elliptic Curve details into the server context
    if (!eecdhCurve.isEmpty()) {
        debugs(83, 9, "Setting Ephemeral ECDH curve to " << eecdhCurve << ".");

#if USE_OPENSSL && OPENSSL_VERSION_NUMBER >= 0x0090800fL && !defined(OPENSSL_NO_ECDH)
        int nid = OBJ_sn2nid(eecdhCurve.c_str());
        if (!nid) {
            debugs(83, DBG_CRITICAL, "ERROR: Unknown EECDH curve '" << eecdhCurve << "'");
            return;
        }

        auto ecdh = EC_KEY_new_by_curve_name(nid);
        if (!ecdh) {
            const auto x = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Unable to configure Ephemeral ECDH: " << Security::ErrorString(x));
            return;
        }

        if (!SSL_CTX_set_tmp_ecdh(ctx.get(), ecdh)) {
            const auto x = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Unable to set Ephemeral ECDH: " << Security::ErrorString(x));
        }
        EC_KEY_free(ecdh);

#else
        debugs(83, DBG_CRITICAL, "ERROR: EECDH is not available in this build." <<
               " Please link against OpenSSL>=0.9.8 and ensure OPENSSL_NO_ECDH is not set.");
#endif
    }

    // set DH parameters into the server context
#if USE_OPENSSL
    if (parsedDhParams) {
        SSL_CTX_set_tmp_dh(ctx.get(), parsedDhParams.get());
    }
#endif
}