static int
authDigestNonceLastRequest(digest_nonce_h * nonce)
{
    if (!nonce)
        return -1;

    if (nonce->nc == 99999997) {
        debugs(29, 4, "authDigestNoncelastRequest: Nonce count about to overflow");
        return -1;
    }

    if (nonce->nc >= digestConfig.noncemaxuses - 1) {
        debugs(29, 4, "authDigestNoncelastRequest: Nonce count about to hit user limit");
        return -1;
    }

    /* and other tests are possible. */
    return 0;
}