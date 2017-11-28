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
    field += xcountws(field);

    if (!*field)		/* no authorization cookie */
        return NULL;

    return base64_decode(field);
}