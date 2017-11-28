static char
wccp2_update_md5_security(char *password, char *ptr, char *packet, int len)
{
    uint8_t md5Digest[SQUID_MD5_DIGEST_LENGTH];
    char pwd[WCCP2_PASSWORD_LEN];
    SquidMD5_CTX M;

    struct wccp2_security_md5_t *ws;

    debugs(80, 5, "wccp2_update_md5_security: called");

    /* The password field, for the MD5 hash, needs to be 8 bytes and NUL padded. */
    memset(pwd, 0, sizeof(pwd));
    strncpy(pwd, password, sizeof(pwd));
    pwd[sizeof(pwd) - 1] = '\0';

    ws = (struct wccp2_security_md5_t *) ptr;
    assert(ntohs(ws->security_type) == WCCP2_SECURITY_INFO);
    /* Its the security part */

    if (ntohl(ws->security_option) != WCCP2_MD5_SECURITY) {
        debugs(80, 5, "wccp2_update_md5_security: this service ain't md5'ing, abort");
        return 0;
    }

    /* And now its the MD5 section! */
    /* According to the draft, the MD5 security hash is the combination of
     * the 8-octet password (padded w/ NUL bytes) and the entire WCCP packet,
     * including the WCCP message header. The WCCP security implementation
     * area should be zero'ed before calculating the MD5 hash.
     */
    /* XXX eventually we should be able to kill md5Digest and blit it directly in */
    memset(ws->security_implementation, 0, sizeof(ws->security_implementation));

    SquidMD5Init(&M);

    SquidMD5Update(&M, pwd, sizeof(pwd));

    SquidMD5Update(&M, packet, len);

    SquidMD5Final(md5Digest, &M);

    memcpy(ws->security_implementation, md5Digest, sizeof(md5Digest));

    /* Finished! */
    return 1;
}