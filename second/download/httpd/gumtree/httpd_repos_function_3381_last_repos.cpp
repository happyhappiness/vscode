static apr_uint64_t ap_siphash24(const void *src, apr_size_t len,
                                 const unsigned char key[AP_SIPHASH_KSIZE])
{
    const unsigned char *ptr, *end;
    apr_uint64_t v0, v1, v2, v3, m;
    apr_uint64_t k0, k1;
    unsigned int rem;

    k0 = U8TO64_LE(key + 0);
    k1 = U8TO64_LE(key + 8);
    v3 = k1 ^ (apr_uint64_t)0x7465646279746573ULL;
    v2 = k0 ^ (apr_uint64_t)0x6c7967656e657261ULL;
    v1 = k1 ^ (apr_uint64_t)0x646f72616e646f6dULL;
    v0 = k0 ^ (apr_uint64_t)0x736f6d6570736575ULL;

    rem = (unsigned int)(len & 0x7);
    for (ptr = src, end = ptr + len - rem; ptr < end; ptr += 8) {
        m = U8TO64_LE(ptr);
        v3 ^= m;
        SIPROUND();
        SIPROUND();
        v0 ^= m;
    }
    m = (apr_uint64_t)(len & 0xff) << 56;
    switch (rem) {
        case 7: m |= (apr_uint64_t)ptr[6] << 48;
        case 6: m |= (apr_uint64_t)ptr[5] << 40;
        case 5: m |= (apr_uint64_t)ptr[4] << 32;
        case 4: m |= (apr_uint64_t)ptr[3] << 24;
        case 3: m |= (apr_uint64_t)ptr[2] << 16;
        case 2: m |= (apr_uint64_t)ptr[1] << 8;
        case 1: m |= (apr_uint64_t)ptr[0];
        case 0: break;
    }
    v3 ^= m;
    SIPROUND();
    SIPROUND();
    v0 ^= m;

    v2 ^= 0xff;
    SIPROUND();
    SIPROUND();
    SIPROUND();
    SIPROUND();

    return v0 ^ v1 ^ v2 ^ v3;
}