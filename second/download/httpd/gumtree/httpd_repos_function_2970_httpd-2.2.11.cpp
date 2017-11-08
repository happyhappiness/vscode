static int true_random(void)
{
    apr_uint64_t time_now;

#if APR_HAS_RANDOM
    unsigned char buf[2];

    if (apr_generate_random_bytes(buf, 2) == APR_SUCCESS) {
        return (buf[0] << 8) | buf[1];
    }
#endif

    /* crap. this isn't crypto quality, but it will be Good Enough */

    time_now = apr_time_now();
    srand((unsigned int)(((time_now >> 32) ^ time_now) & 0xffffffff));

    return rand() & 0x0FFFF;
}