uint32_t
crc32_buffer(const unsigned char *s, size_t len)
{
    size_t      i;
    uint32_t   ret;

    ret = 0;
    for (i = 0;  i < len;  i++)
        ret = crc32_tab[(ret ^ s[i]) & 0xff] ^ (ret >> 8);
    return ret;
}