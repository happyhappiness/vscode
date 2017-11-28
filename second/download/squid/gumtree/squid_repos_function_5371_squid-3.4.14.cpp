int
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
    if (!static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->CheckNonceCount) {
        /* Ignore client supplied NC */
        intnc = nonce->nc + 1;
    }

    if ((static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->NonceStrictness && intnc != nonce->nc + 1) ||
            intnc < nonce->nc + 1) {
        debugs(29, 4, "authDigestNonceIsValid: Nonce count doesn't match");
        nonce->flags.valid = false;
        return 0;
    }

    /* increment the nonce count - we've already checked that intnc is a
     *  valid representation for us, so we don't need the test here.
     */
    nonce->nc = intnc;

    return !authDigestNonceIsStale(nonce);
}