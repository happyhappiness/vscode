void
ebcdic2ascii_strictly(unsigned char *dest, const unsigned char *srce, size_t count)
{
        while (count-- != 0) {
                *dest++ = os_toascii_strictly[*srce++];
        }
}