static int
ntlmDecodeAuth(struct ntlm_authenticate *auth, char *buf, size_t size)
{
    const char *p;
    char *origbuf;
    int s;

    if (!buf) {
        return 1;
    }
    origbuf = buf;
    if (ntlmCheckHeader(&auth->hdr, NTLM_AUTHENTICATE)) {
        fprintf(stderr, "ntlmDecodeAuth: header check fails\n");
        return -1;
    }
    debug("ntlmDecodeAuth: size of %d\n", (int) size);
    debug("ntlmDecodeAuth: flg %08x\n", auth->flags);
    debug("ntlmDecodeAuth: usr o(%d) l(%d)\n", auth->user.offset, auth->user.len);

    if ((p = ntlmGetString(&auth->hdr, &auth->domain, auth->flags)) == NULL)
        p = authenticate_ntlm_domain;

    debug("ntlmDecodeAuth: Domain '%s'.\n", p);

    if ((s = strlen(p) + 1) >= size)
        return 1;
    strcpy(buf, p);

    debug("ntlmDecodeAuth: Domain '%s'.\n", buf);

    size -= s;
    buf += (s - 1);
    *buf++ = '\\';		/* Using \ is more consistent with MS-proxy */

    if ( (p = ntlmGetString(&auth->hdr, &auth->user, auth->flags)) == NULL)
        return 1;

    if ((s = strlen(p) + 1) >= size)
        return 1;

    while (*p)
        *buf++ = (*p++);	//tolower

    *buf++ = '\0';
    size -= s;

    debug("ntlmDecodeAuth: user: %s%s\n", origbuf, p);

    return 0;
}