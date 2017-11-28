void
ntlm_make_nonce(char *nonce)
{
    static std::mt19937 mt(time(0));
    static xuniform_int_distribution<uint8_t> dist;

    for (int i = 0; i < NTLM_NONCE_LEN; ++i)
        nonce[i] = static_cast<char>(dist(mt) & 0xFF);
}