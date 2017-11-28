char *
fetch_credentials(ntlm_authenticate * auth, int auth_length)
{
    char *p = credentials;
    lstring tmp;
    tmp = ntlm_fetch_string((char *) auth, auth_length, &auth->domain);
    *p = '\0';
    if (tmp.str == NULL)
        return NULL;
    memcpy(p, tmp.str, tmp.l);
    p += tmp.l;
    *p++ = '\\';
    *p = '\0';
    tmp = ntlm_fetch_string((char *) auth, auth_length, &auth->user);
    if (tmp.str == NULL)
        return NULL;
    memcpy(p, tmp.str, tmp.l);
    *(p + tmp.l) = '\0';
    return credentials;
}