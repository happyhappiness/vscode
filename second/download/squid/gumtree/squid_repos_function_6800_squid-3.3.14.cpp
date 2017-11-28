int
ntlm_unpack_auth(const ntlm_authenticate *auth, char *user, char *domain, const int32_t size)
{
    lstring rv;

    if (ntlm_validate_packet(&auth->hdr, NTLM_AUTHENTICATE)) {
        fprintf(stderr, "ntlm_unpack_auth: header check fails\n");
        return NTLM_ERR_PROTOCOL;
    }
    debug("ntlm_unpack_auth: size of %d\n", size);
    debug("ntlm_unpack_auth: flg %08x\n", auth->flags);
    debug("ntlm_unpack_auth: lmr o(%d) l(%d)\n", le32toh(auth->lmresponse.offset), auth->lmresponse.len);
    debug("ntlm_unpack_auth: ntr o(%d) l(%d)\n", le32toh(auth->ntresponse.offset), auth->ntresponse.len);
    debug("ntlm_unpack_auth: dom o(%d) l(%d)\n", le32toh(auth->domain.offset), auth->domain.len);
    debug("ntlm_unpack_auth: usr o(%d) l(%d)\n", le32toh(auth->user.offset), auth->user.len);
    debug("ntlm_unpack_auth: wst o(%d) l(%d)\n", le32toh(auth->workstation.offset), auth->workstation.len);
    debug("ntlm_unpack_auth: key o(%d) l(%d)\n", le32toh(auth->sessionkey.offset), auth->sessionkey.len);

    rv = ntlm_fetch_string(&auth->hdr, size, &auth->domain, auth->flags);
    if (rv.l > 0) {
        memcpy(domain, rv.str, rv.l);
        domain[rv.l] = '\0';
        debug("ntlm_unpack_auth: Domain '%s' (len=%d).\n", domain, rv.l);
    }
    if (rv.l >= size) {
        debug("ntlm_unpack_auth: Domain length %d too big for %d byte packet.\n", rv.l , size);
        return NTLM_ERR_BLOB;
    }

    rv = ntlm_fetch_string(&auth->hdr, size, &auth->user, auth->flags);
    if (rv.l > 0) {
        memcpy(user, rv.str, rv.l);
        user[rv.l] = '\0';
        debug("ntlm_unpack_auth: Username '%s' (len=%d).\n", user, rv.l);
    } else
        return NTLM_ERR_LOGON;

    return NTLM_ERR_NONE;
}