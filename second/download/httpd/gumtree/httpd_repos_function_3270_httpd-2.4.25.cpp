static int ap_crypto_equals(const void *buf1, const void *buf2,
                            apr_size_t size)
{
    const unsigned char *p1 = buf1;
    const unsigned char *p2 = buf2;
    unsigned char diff = 0;
    apr_size_t i;

    for (i = 0; i < size; ++i) {
        diff |= p1[i] ^ p2[i];
    }

    return 1 & ((diff - 1) >> 8);
}