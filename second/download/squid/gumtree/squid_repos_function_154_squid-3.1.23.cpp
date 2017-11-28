void ska_base64_decode(char* result, const char *data, int result_size)
{
    int j;
    int c;
    long val;
    if (!data)
        return;
    if (!base64_initialized)
        ska_base64_init();
    val = c = 0;

    for (j = 0; *data ; data++) {
        unsigned int k = ((unsigned char) *data) % BASE64_VALUE_SZ;
        if (base64_value[k] < 0)
            continue;
        val <<= 6;
        val += base64_value[k];
        if (++c < 4)
            continue;
        /* One quantum of four encoding characters/24 bit */
        if (j >= result_size)
            break;
        result[j++] = val >> 16;	/* High 8 bits */
        if (j >= result_size)
            break;
        result[j++] = (val >> 8) & 0xff;	/* Mid 8 bits */
        if (j >= result_size)
            break;
        result[j++] = val & 0xff;	/* Low 8 bits */
        val = c = 0;
    }
    return;
}