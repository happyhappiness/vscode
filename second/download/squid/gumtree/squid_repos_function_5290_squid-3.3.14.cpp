static int
authDigestNonceIsStale(digest_nonce_h * nonce)
{
    /* do we have a nonce ? */

    if (!nonce)
        return -1;

    /* has it's max duration expired? */
    if (nonce->noncedata.creationtime + static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->noncemaxduration < current_time.tv_sec) {
        debugs(29, 4, "authDigestNonceIsStale: Nonce is too old. " <<
               nonce->noncedata.creationtime << " " <<
               static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->noncemaxduration << " " <<
               current_time.tv_sec);

        nonce->flags.valid = 0;
        return -1;
    }

    if (nonce->nc > 99999998) {
        debugs(29, 4, "authDigestNonceIsStale: Nonce count overflow");
        nonce->flags.valid = 0;
        return -1;
    }

    if (nonce->nc > static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->noncemaxuses) {
        debugs(29, 4, "authDigestNoncelastRequest: Nonce count over user limit");
        nonce->flags.valid = 0;
        return -1;
    }

    /* seems ok */
    return 0;
}