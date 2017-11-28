SSL_METHOD *
#else
const SSL_METHOD *
#endif
Ssl::method(int version)
{
    switch (version) {

    case 2:
#if !defined(OPENSSL_NO_SSL2)
        debugs(83, 5, "Using SSLv2.");
        return SSLv2_client_method();
#else
        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 3:
#if !defined(OPENSSL_NO_SSL3)
        debugs(83, 5, "Using SSLv3.");
        return SSLv3_client_method();
#else
        debugs(83, DBG_IMPORTANT, "SSLv3 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 4:
        debugs(83, 5, "Using TLSv1.");
        return TLSv1_client_method();
        break;

    case 5:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.1.");
        return TLSv1_1_client_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 6:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.2");
        return TLSv1_2_client_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 1:

    default:
        debugs(83, 5, "Using SSLv2/SSLv3.");
        return SSLv23_client_method();
        break;
    }

    //Not reached
    return NULL;
}