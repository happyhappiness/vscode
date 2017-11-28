int
base64_decode(char *result, unsigned int result_size, const char *p)
{
    int j = 0;
    int c;
    long val;
    if (!p || !result || result_size == 0)
        return j;
    if (!base64_initialized)
        base64_init();
    val = c = 0;
    for (; *p; p++) {
        unsigned int k = ((unsigned char) *p) % BASE64_VALUE_SZ;
        if (base64_value[k] < 0)
            continue;
        val <<= 6;
        val += base64_value[k];
        if (++c < 4)
            continue;
        /* One quantum of four encoding characters/24 bit */
        if (j+4 <= result_size) {
            // Speed optimization: plenty of space, avoid some per-byte checks.
            result[j++] = (val >> 16) & 0xff;   /* High 8 bits */
            result[j++] = (val >> 8) & 0xff;    /* Mid 8 bits */
            result[j++] = val & 0xff;       /* Low 8 bits */
        } else {
            // part-quantum goes a bit slower with per-byte checks
            result[j++] = (val >> 16) & 0xff;   /* High 8 bits */
            if (j == result_size)
                return j;
            result[j++] = (val >> 8) & 0xff;    /* Mid 8 bits */
            if (j == result_size)
                return j;
            result[j++] = val & 0xff;       /* Low 8 bits */
        }
        if (j == result_size)
            return j;
        val = c = 0;
    }
    return j;
}