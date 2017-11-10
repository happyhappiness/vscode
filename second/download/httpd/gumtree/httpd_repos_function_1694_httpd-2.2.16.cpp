static apr_size_t bndm(bndm_t *t, const char *h, apr_size_t hl)
{
    const char *skip;
    const char *he, *p, *pi;
    unsigned int *T, x, d;
    apr_size_t nl;

    he = h + hl;

    T = t->T;
    x = t->x;
    nl = t->pattern_len;

    pi = h - 1; /* pi: p initial */
    p = pi + nl; /* compare window right to left. point to the first char */

    while (p < he) {
        skip = p;
        d = x;
        do {
            d &= T[(unsigned char) *p--];
            if (!d) {
                break;
            }
            if ((d & 1)) {
                if (p != pi) {
                    skip = p;
                }
                else {
                    return p - h + 1;
                }
            }
            d >>= 1;
        } while (d);

        pi = skip;
        p = pi + nl;
    }

    return hl;
}