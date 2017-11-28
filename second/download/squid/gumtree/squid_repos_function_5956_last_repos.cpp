digest_nonce_h *
authenticateDigestNonceNew(void)
{
    digest_nonce_h *newnonce = static_cast < digest_nonce_h * >(digest_nonce_pool->alloc());

    /* NONCE CREATION - NOTES AND REASONING. RBC 20010108
     * === EXCERPT FROM RFC 2617 ===
     * The contents of the nonce are implementation dependent. The quality
     * of the implementation depends on a good choice. A nonce might, for
     * example, be constructed as the base 64 encoding of
     *
     * time-stamp H(time-stamp ":" ETag ":" private-key)
     *
     * where time-stamp is a server-generated time or other non-repeating
     * value, ETag is the value of the HTTP ETag header associated with
     * the requested entity, and private-key is data known only to the
     * server.  With a nonce of this form a server would recalculate the
     * hash portion after receiving the client authentication header and
     * reject the request if it did not match the nonce from that header
     * or if the time-stamp value is not recent enough. In this way the
     * server can limit the time of the nonce's validity. The inclusion of
     * the ETag prevents a replay request for an updated version of the
     * resource.  (Note: including the IP address of the client in the
     * nonce would appear to offer the server the ability to limit the
     * reuse of the nonce to the same client that originally got it.
     * However, that would break proxy farms, where requests from a single
     * user often go through different proxies in the farm. Also, IP
     * address spoofing is not that hard.)
     * ====
     *
     * Now for my reasoning:
     * We will not accept a unrecognised nonce->we have all recognisable
     * nonces stored. If we send out unique base64 encodings we guarantee
     * that a given nonce applies to only one user (barring attacks or
     * really bad timing with expiry and creation).  Using a random
     * component in the nonce allows us to loop to find a unique nonce.
     * We use H(nonce_data) so the nonce is meaningless to the reciever.
     * So our nonce looks like base64(H(timestamp,pointertohash,randomdata))
     * And even if our randomness is not very random we don't really care
     * - the timestamp and memory pointer also guarantee local uniqueness
     * in the input to the hash function.
     */
    // NP: this will likely produce the same randomness sequences for each worker
    // since they should all start within the 1-second resolution of seed value.
    static std::mt19937 mt(static_cast<uint32_t>(getCurrentTime() & 0xFFFFFFFF));
    static xuniform_int_distribution<uint32_t> newRandomData;

    /* create a new nonce */
    newnonce->nc = 0;
    newnonce->flags.valid = true;
    newnonce->noncedata.self = newnonce;
    newnonce->noncedata.creationtime = current_time.tv_sec;
    newnonce->noncedata.randomdata = newRandomData(mt);

    authDigestNonceEncode(newnonce);

    // ensure temporal uniqueness by checking for existing nonce
    while (authenticateDigestNonceFindNonce((char const *) (newnonce->key))) {
        /* create a new nonce */
        newnonce->noncedata.randomdata = newRandomData(mt);
        authDigestNonceEncode(newnonce);
    }

    hash_join(digest_nonce_cache, newnonce);
    /* the cache's link */
    authDigestNonceLink(newnonce);
    newnonce->flags.incache = true;
    debugs(29, 5, "created nonce " << newnonce << " at " << newnonce->noncedata.creationtime);
    return newnonce;
}