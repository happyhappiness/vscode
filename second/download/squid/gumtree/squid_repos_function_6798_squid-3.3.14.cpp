void
ntlm_make_nonce(char *nonce)
{
    static unsigned hash;
    int i;
    int r = (int) rand();
    r = (hash ^ r) + r;

    for (i = 0; i < NTLM_NONCE_LEN; ++i) {
        nonce[i] = r;
        r = (r >> 2) ^ r;
    }
    hash = r;
}