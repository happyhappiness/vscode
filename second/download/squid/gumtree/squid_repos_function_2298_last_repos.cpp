const char *
HttpHeader::getAuth(Http::HdrType id, const char *auth_scheme) const
{
    const char *field;
    int l;
    assert(auth_scheme);
    field = getStr(id);

    if (!field)         /* no authorization field */
        return NULL;

    l = strlen(auth_scheme);

    if (!l || strncasecmp(field, auth_scheme, l))   /* wrong scheme */
        return NULL;

    field += l;

    if (!xisspace(*field))  /* wrong scheme */
        return NULL;

    /* skip white space */
    for (; field && xisspace(*field); ++field);

    if (!*field)        /* no authorization cookie */
        return NULL;

    static char decodedAuthToken[8192];
    struct base64_decode_ctx ctx;
    base64_decode_init(&ctx);
    size_t decodedLen = 0;
    if (!base64_decode_update(&ctx, &decodedLen, reinterpret_cast<uint8_t*>(decodedAuthToken), strlen(field), reinterpret_cast<const uint8_t*>(field)) ||
            !base64_decode_final(&ctx)) {
        return NULL;
    }
    decodedAuthToken[decodedLen] = '\0';
    return decodedAuthToken;
}