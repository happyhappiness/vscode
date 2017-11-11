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
        default:
            break;
    }
    return cp;
}