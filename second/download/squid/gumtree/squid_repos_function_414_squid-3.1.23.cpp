static int
validUsername(const char *user)
{
    const unsigned char *p = (const unsigned char *) user;

    /* Leading whitespace? */
    if (xisspace(p[0]))
        return 0;
    while (p[0] && p[1]) {
        if (xisspace(p[0])) {
            /* More than one consequitive space? */
            if (xisspace(p[1]))
                return 0;
            /* or odd space type character used? */
            if (p[0] != ' ')
                return 0;
        }
        p++;
    }
    /* Trailing whitespace? */
    if (xisspace(p[0]))
        return 0;
    return 1;
}