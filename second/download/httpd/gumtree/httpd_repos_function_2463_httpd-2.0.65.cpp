static void Decode(apr_uint32_t *output, const unsigned char *input,
                   unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((apr_uint32_t)input[j])             |
                    (((apr_uint32_t)input[j + 1]) << 8)  |
                    (((apr_uint32_t)input[j + 2]) << 16) |
                    (((apr_uint32_t)input[j + 3]) << 24);
}