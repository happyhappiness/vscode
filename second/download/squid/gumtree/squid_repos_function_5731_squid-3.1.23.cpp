char *
base64_decode(const char *p)
{
    static char result[BASE64_RESULT_SZ];
    int j;
    int c;
    long val;
    if (!p)
        return NULL;
    if (!base64_initialized)
        base64_init();
    val = c = 0;
    for (j = 0; *p && j + 4 < BASE64_RESULT_SZ; p++) {
        unsigned int k = ((unsigned char) *p) % BASE64_VALUE_SZ;
        if (base64_value[k] < 0)
            continue;
        val <<= 6;
        val += base64_value[k];
        if (++c < 4)
            continue;
        /* One quantum of four encoding characters/24 bit */
        result[j++] = (val >> 16) & 0xff;	/* High 8 bits */
        result[j++] = (val >> 8) & 0xff;	/* Mid 8 bits */
        result[j++] = val & 0xff;	/* Low 8 bits */
        val = c = 0;
    }
    result[j] = 0;
    return result;
}