int
bcmp_translate(unsigned char const *s1, unsigned char const*s2, register int len, char *translate)
{
    register unsigned char const *p1 = s1, *p2 = s2;
    while (len) {
        if (translate[*p1++] != translate[*p2++])
            return 1;
        len--;
    }
    return 0;
}