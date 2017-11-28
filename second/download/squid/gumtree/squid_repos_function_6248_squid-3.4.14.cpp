char *
Format::QuoteMimeBlob(const char *header)
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
    /**
     * Whe OLD_LOG_MIME is defined we escape: \x00-\x1F"#%;<>?{}|\\\\^~`\[\]\x7F-\xFF
     * which is the default escape list for the CPAN Perl5 URI module
     * modulo the inclusion of space (x40) to make the raw logs a bit
     * more readable.
     */

    while ((c = *(const unsigned char *) header++) != '\0') {
#if !OLD_LOG_MIME
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
        } else
#endif
            if (c <= 0x1F
                    || c >= 0x7F
                    || c == '%'
#if OLD_LOG_MIME
                    || c == '"'
                    || c == '#'
                    || c == ';'
                    || c == '<'
                    || c == '>'
                    || c == '?'
                    || c == '{'
                    || c == '}'
                    || c == '|'
                    || c == '\\'
                    || c == '^'
                    || c == '~'
                    || c == '`'
#endif
                    || c == '['
                    || c == ']') {
                *buf_cursor = '%';
                ++buf_cursor;
                i = c * 2;
                *buf_cursor = c2x[i];
                ++buf_cursor;
                *buf_cursor = c2x[i + 1];
                ++buf_cursor;
#if !OLD_LOG_MIME

            } else if (c == '\\') {
                *buf_cursor = '\\';
                ++buf_cursor;
                *buf_cursor = '\\';
                ++buf_cursor;
#endif

            } else {
                *buf_cursor = (char) c;
                ++buf_cursor;
            }
    }

    *buf_cursor = '\0';
    return buf;
}