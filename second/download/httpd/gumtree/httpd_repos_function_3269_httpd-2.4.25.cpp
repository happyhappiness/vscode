static void ap_siphash24_auth(unsigned char out[AP_SIPHASH_DSIZE],
                              const void *src, apr_size_t len,
                              const unsigned char key[AP_SIPHASH_KSIZE])
{
    apr_uint64_t h;
    h = ap_siphash24(src, len, key);
    U64TO8_LE(out, h);
}