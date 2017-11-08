void
ebcdic2ascii(unsigned char *dest, const unsigned char *srce, size_t count)
{
        while (count-- != 0) {
                *dest++ = os_toascii[*srce++];
        }
}