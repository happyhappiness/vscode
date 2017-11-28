int
matchDomainName(const char *h, const char *d)
{
    int dl;
    int hl;

    while ('.' == *h)
        ++h;

    hl = strlen(h);

    dl = strlen(d);

    /*
     * Start at the ends of the two strings and work towards the
     * beginning.
     */
    while (xtolower(h[--hl]) == xtolower(d[--dl])) {
        if (hl == 0 && dl == 0) {
            /*
             * We made it all the way to the beginning of both
             * strings without finding any difference.
             */
            return 0;
        }

        if (0 == hl) {
            /*
             * The host string is shorter than the domain string.
             * There is only one case when this can be a match.
             * If the domain is just one character longer, and if
             * that character is a leading '.' then we call it a
             * match.
             */

            if (1 == dl && '.' == d[0])
                return 0;
            else
                return -1;
        }

        if (0 == dl) {
            /*
             * The domain string is shorter than the host string.
             * This is a match only if the first domain character
             * is a leading '.'.
             */

            if ('.' == d[0])
                return 0;
            else
                return 1;
        }
    }

    /*
     * We found different characters in the same position (from the end).
     */
    /*
     * If one of those character is '.' then its special.  In order
     * for splay tree sorting to work properly, "x-foo.com" must
     * be greater than ".foo.com" even though '-' is less than '.'.
     */
    if ('.' == d[dl])
        return 1;

    if ('.' == h[hl])
        return -1;

    return (xtolower(h[hl]) - xtolower(d[dl]));
}