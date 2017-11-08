char *SSL_SESSION_id2sz(unsigned char *id, int idlen,
                        char *str, int strsize)
{
    char *cp;
    int n;

    cp = str;
    for (n = 0; n < idlen && n < SSL_MAX_SSL_SESSION_ID_LENGTH; n++) {
        apr_snprintf(cp, strsize - (cp-str), "%02X", id[n]);
        cp += 2;
    }
    *cp = NUL;
    return str;
}