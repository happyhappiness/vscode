int
strListGetItem(const String * str, char del, const char **item, int *ilen, const char **pos)
{
    size_t len;
    /* ',' is always enabled as field delimiter as this is required for
     * processing merged header values properly, even if Cookie normally
     * uses ';' as delimiter.
     */
    static char delim[3][8] = {
        "\"?,",
        "\"\\",
        " ?,\t\r\n"
    };
    int quoted = 0;
    assert(str && item && pos);

    delim[0][1] = del;
    delim[2][1] = del;

    if (!*pos) {
        *pos = str->termedBuf();

        if (!*pos)
            return 0;
    }

    /* skip leading whitespace and delimiters */
    *pos += strspn(*pos, delim[2]);

    *item = *pos;		/* remember item's start */

    /* find next delimiter */
    do {
        *pos += strcspn(*pos, delim[quoted]);
        if (**pos == '"') {
            quoted = !quoted;
            *pos += 1;
        } else if (quoted && **pos == '\\') {
            *pos += 1;
            if (**pos)
                *pos += 1;
        } else {
            break;		/* Delimiter found, marking the end of this value */
        }
    } while (**pos);

    len = *pos - *item;		/* *pos points to del or '\0' */

    /* rtrim */
    while (len > 0 && xisspace((*item)[len - 1]))
        len--;

    if (ilen)
        *ilen = len;

    return len > 0;
}