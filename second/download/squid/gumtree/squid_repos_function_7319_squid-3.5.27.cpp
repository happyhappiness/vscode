void
rfc1738_unescape(char *s)
{
    int i, j;           /* i is write, j is read */
    for (i = j = 0; s[j]; i++, j++) {
        s[i] = s[j];
        if (s[j] != '%') {
            /* normal case, nothing more to do */
        } else if (s[j + 1] == '%') {   /* %% case */
            j++;        /* Skip % */
        } else {
            /* decode */
            int v1, v2, x;
            v1 = fromhex(s[j + 1]);
            if (v1 < 0)
                continue;  /* non-hex or \0 */
            v2 = fromhex(s[j + 2]);
            if (v2 < 0)
                continue;  /* non-hex or \0 */
            x = v1 << 4 | v2;
            if (x > 0 && x <= 255) {
                s[i] = x;
                j += 2;
            }
        }
    }
    s[i] = '\0';
}