static char

wccp2_check_security(struct wccp2_service_list_t *srv, char *security, char *packet, int len)
{

    struct wccp2_security_md5_t *ws = (struct wccp2_security_md5_t *) security;
    uint8_t md5Digest[SQUID_MD5_DIGEST_LENGTH], md5_challenge[SQUID_MD5_DIGEST_LENGTH];
    char pwd[WCCP2_PASSWORD_LEN];
    SquidMD5_CTX M;

    /* Make sure the security type matches what we expect */

    if (ntohl(ws->security_option) != srv->wccp2_security_type) {
        debugs(80, DBG_IMPORTANT, "wccp2_check_security: received packet has the wrong security option");
        return 0;
    }

    if (srv->wccp2_security_type == WCCP2_NO_SECURITY) {
        return 1;
    }

    if (srv->wccp2_security_type != WCCP2_MD5_SECURITY) {
        debugs(80, DBG_IMPORTANT, "wccp2_check_security: invalid security option");
        return 0;
    }

    /* If execution makes it here then we have an MD5 security */

    /* The password field, for the MD5 hash, needs to be 8 bytes and NUL padded. */
    memset(pwd, 0, sizeof(pwd));
    strncpy(pwd, srv->wccp_password, sizeof(pwd));
    pwd[sizeof(pwd) - 1] = '\0';

    /* Take a copy of the challenge: we need to NUL it before comparing */
    memcpy(md5_challenge, ws->security_implementation, sizeof(md5_challenge));

    memset(ws->security_implementation, 0, sizeof(ws->security_implementation));

    SquidMD5Init(&M);

    SquidMD5Update(&M, pwd, sizeof(pwd));

    SquidMD5Update(&M, packet, len);

    SquidMD5Final(md5Digest, &M);

    return (memcmp(md5Digest, md5_challenge, SQUID_MD5_DIGEST_LENGTH) == 0);
}