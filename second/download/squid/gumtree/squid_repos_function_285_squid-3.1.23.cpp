void
ntlmMakeChallenge(struct ntlm_challenge *chal, int32_t flags)
{
    static unsigned hash;
    int r;
    int i;

    debug("ntlmMakeChallenge: flg %08x\n", flags);

    memset(chal, 0, sizeof(*chal));
    memcpy(chal->hdr.signature, "NTLMSSP", 8);
    chal->flags = htole32(CHALLENGE_TARGET_IS_DOMAIN |
                          NEGOTIATE_ALWAYS_SIGN |
                          NEGOTIATE_USE_NTLM |
                          NEGOTIATE_REQUEST_TARGET |
                          (NEGOTIATE_UNICODE & flags ? NEGOTIATE_UNICODE : NEGOTIATE_ASCII)
                         );
    chal->hdr.type = htole32(NTLM_CHALLENGE);
    chal->flags = flags;
    chal->unknown[6] = htole16(0x003a);

    i = 0;

    if (authenticate_ntlm_domain != NULL)
        while (authenticate_ntlm_domain[i++]);

    chal->flags = flags;
    chal->target.offset = htole32(48);
    chal->target.maxlen = htole16(i);
    chal->target.len = chal->target.maxlen;

    r = (int) rand();
    r = (hash ^ r) + r;

    for (i = 0; i < 8; i++) {
        chal->challenge[i] = r;
        r = (r >> 2) ^ r;
    }

    hash = r;
}