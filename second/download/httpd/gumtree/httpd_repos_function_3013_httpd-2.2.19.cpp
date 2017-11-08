static void Encode(unsigned char *output, const apr_uint32_t *input,
                   unsigned int len)
{
    unsigned int i, j;
    apr_uint32_t k;

    for (i = 0, j = 0; j < len; i++, j += 4) {
        k = input[i];
        output[j]     = (unsigned char)(k & 0xff);
        output[j + 1] = (unsigned char)((k >> 8)  & 0xff);
        output[j + 2] = (unsigned char)((k >> 16) & 0xff);
        output[j + 3] = (unsigned char)((k >> 24) & 0xff);
    }
}