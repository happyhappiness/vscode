char *SSL_SESSION_id2sz(unsigned char *id, int idlen,
                        char *str, int strsize)
{
    if (idlen > SSL_MAX_SSL_SESSION_ID_LENGTH)
        idlen = SSL_MAX_SSL_SESSION_ID_LENGTH;
        
    /* We must ensure not to process more than what would fit in the
     * destination buffer, including terminating NULL */
    if (idlen > (strsize-1) / 2)
        idlen = (strsize-1) / 2;

    ap_bin2hex(id, idlen, str);

    return str;
}