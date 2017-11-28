static int
inet_pton4(const char *src, u_char *dst)
{
    static const char digits[] = "0123456789";
    int saw_digit, octets, ch;
    u_char tmp[NS_INADDRSZ], *tp;

    saw_digit = 0;
    octets = 0;
    *(tp = tmp) = 0;
    while ((ch = *src++) != '\0') {
        const char *pch;

        if ((pch = strchr(digits, ch)) != NULL) {
            u_int nw = *tp * 10 + (pch - digits);

            if (saw_digit && *tp == 0)
                return (0);
            if (nw > 255)
                return (0);
            *tp = nw;
            if (!saw_digit) {
                if (++octets > 4)
                    return (0);
                saw_digit = 1;
            }
        } else if (ch == '.' && saw_digit) {
            if (octets == 4)
                return (0);
            *++tp = 0;
            saw_digit = 0;
        } else
            return (0);
    }
    if (octets < 4)
        return (0);
    memcpy(dst, tmp, NS_INADDRSZ);
    return (1);
}