static char *
username_quote(const char *header)
{
    int c;
    int i;
    char *buf;
    char *buf_cursor;

    if (header == NULL) {
        buf = static_cast<char *>(xcalloc(1, 1));
        *buf = '\0';
        return buf;
    }

    buf = static_cast<char *>(xcalloc(1, (strlen(header) * 3) + 1));
    buf_cursor = buf;
    /*
     * We escape: space \x00-\x1F and space (0x40) and \x7F-\xFF
     * to prevent garbage in the logs. CR and LF are also there just in case.
     */

    while ((c = *(const unsigned char *) header++) != '\0') {
        if (c == '\r') {
            *buf_cursor = '\\';
            ++buf_cursor;
            *buf_cursor = 'r';
            ++buf_cursor;
        } else if (c == '\n') {
            *buf_cursor = '\\';
            ++buf_cursor;
            *buf_cursor = 'n';
            ++buf_cursor;
        } else if (c <= 0x1F
                   || c >= 0x7F
                   || c == '%'
                   || c == ' ') {
            *buf_cursor = '%';
            ++buf_cursor;
            i = c * 2;
            *buf_cursor = c2x[i];
            ++buf_cursor;
            *buf_cursor = c2x[i + 1];
            ++buf_cursor;
        } else {
            *buf_cursor = (char) c;
            ++buf_cursor;
        }
    }

    *buf_cursor = '\0';
    return buf;
}