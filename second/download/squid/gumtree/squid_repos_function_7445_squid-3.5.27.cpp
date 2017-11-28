void
ntlm_make_nonce(char *nonce)
{
    static unsigned hash;
    uint32_t r = static_cast<uint32_t>(rand());
    r = (hash ^ r) + r;

    for (int i = 0; i < NTLM_NONCE_LEN; ++i) {
        nonce[i] = static_cast<char>(r & 0xFF);
        r = (r >> 2) ^ r;
    }
    hash = r;
}