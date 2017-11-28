Ssl::ContextMethod
Ssl::contextMethod(int version)
{
    Ssl::ContextMethod method;

    switch (version) {

    case 2:
#if !defined(OPENSSL_NO_SSL2)
        debugs(83, 5, "Using SSLv2.");
        method = SSLv2_server_method();
#else
        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 3:
#if !defined(OPENSSL_NO_SSL3)
        debugs(83, 5, "Using SSLv3.");
        method = SSLv3_server_method();
#else
        debugs(83, DBG_IMPORTANT, "SSLv3 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 4:
        debugs(83, 5, "Using TLSv1.");
        method = TLSv1_server_method();
        break;

    case 5:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.1.");
        method = TLSv1_1_server_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 6:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.2");
        method = TLSv1_2_server_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 1:

    default:
        debugs(83, 5, "Using SSLv2/SSLv3.");
        method = SSLv23_server_method();
        break;
    }
    return method;
}