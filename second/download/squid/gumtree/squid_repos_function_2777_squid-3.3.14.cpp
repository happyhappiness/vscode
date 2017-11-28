const char *
HttpHeader::getAuth(http_hdr_type id, const char *auth_scheme) const
{
    const char *field;
    int l;
    assert(auth_scheme);
    field = getStr(id);

    if (!field)			/* no authorization field */
        return NULL;

    l = strlen(auth_scheme);

    if (!l || strncasecmp(field, auth_scheme, l))	/* wrong scheme */
        return NULL;

    field += l;

    if (!xisspace(*field))	/* wrong scheme */
        return NULL;

    /* skip white space */
    for (; field && xisspace(*field); ++field);

    if (!*field)		/* no authorization cookie */
        return NULL;

    static char decodedAuthToken[8192];
    const int decodedLen = base64_decode(decodedAuthToken, sizeof(decodedAuthToken)-1, field);
    decodedAuthToken[decodedLen] = '\0';
    return decodedAuthToken;
}