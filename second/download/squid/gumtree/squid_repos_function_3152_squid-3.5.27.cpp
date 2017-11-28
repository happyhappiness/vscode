const cache_key *
storeKeyScan(const char *buf)
{
    static unsigned char digest[SQUID_MD5_DIGEST_LENGTH];
    int i;
    int j = 0;
    char t[3];

    for (i = 0; i < SQUID_MD5_DIGEST_LENGTH; ++i) {
        t[0] = *(buf + (j++));
        t[1] = *(buf + (j++));
        t[2] = '\0';
        *(digest + i) = (unsigned char) strtol(t, NULL, 16);
    }

    return digest;
}