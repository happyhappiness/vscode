static int
authDigestNonceIsValid(digest_nonce_h * nonce, char nc[9])
{
    unsigned long intnc;
    /* do we have a nonce ? */

    if (!nonce)
        return 0;

    intnc = strtol(nc, NULL, 16);

    /* has it already been invalidated ? */
    if (!nonce->flags.valid) {
        debugs(29, 4, "authDigestNonceIsValid: Nonce already invalidated");
        return 0;
    }

    /* is the nonce-count ok ? */
    if (!digestConfig.CheckNonceCount) {
        nonce->nc++;
        return -1;              /* forced OK by configuration */
    }

    if ((digestConfig.NonceStrictness && intnc != nonce->nc + 1) ||
            intnc < nonce->nc + 1) {
        debugs(29, 4, "authDigestNonceIsValid: Nonce count doesn't match");
        nonce->flags.valid = 0;
        return 0;
    }

    /* seems ok */
    /* increment the nonce count - we've already checked that intnc is a
     *  valid representation for us, so we don't need the test here.
     */
    nonce->nc = intnc;

    return -1;
}