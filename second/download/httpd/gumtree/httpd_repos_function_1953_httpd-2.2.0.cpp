void
ascii2ebcdic(void *dest, const void *srce, size_t count)
{
        unsigned char *udest = dest;
        const unsigned char *usrce = srce;

        while (count-- != 0) {
                *udest++ = os_toebcdic[*usrce++];
    }
}