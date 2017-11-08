char *ssl_util_algotypestr(ssl_algo_t t)
{
    char *cp;

    cp = "UNKNOWN";
    switch (t) {
        case SSL_ALGO_RSA:
            cp = "RSA";
            break;
        case SSL_ALGO_DSA:
            cp = "DSA";
            break;
#ifdef HAVE_ECC
        case SSL_ALGO_ECC:
            cp = "ECC";
            break;
#endif
        default:
            break;
    }
    return cp;
}