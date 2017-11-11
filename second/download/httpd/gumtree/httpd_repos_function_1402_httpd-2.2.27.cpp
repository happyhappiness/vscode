static long get_chunk_size(char *b)
{
    long chunksize = 0;
    size_t chunkbits = sizeof(long) * 8;

    ap_xlate_proto_from_ascii(b, strlen(b));

    if (!apr_isxdigit(*b)) {
        /*
         * Detect invalid character at beginning. This also works for empty
         * chunk size lines.
         */
        return INVALID_CHAR;
    }
    /* Skip leading zeros */
    while (*b == '0') {
        ++b;
    }

    while (apr_isxdigit(*b) && (chunkbits > 0)) {
        int xvalue = 0;

        if (*b >= '0' && *b <= '9') {
            xvalue = *b - '0';
        }
        else if (*b >= 'A' && *b <= 'F') {
            xvalue = *b - 'A' + 0xa;
        }
        else if (*b >= 'a' && *b <= 'f') {
            xvalue = *b - 'a' + 0xa;
        }

        chunksize = (chunksize << 4) | xvalue;
        chunkbits -= 4;
        ++b;
    }
    if (apr_isxdigit(*b) && (chunkbits <= 0)) {
        /* overflow */
        return -1;
    }

    return chunksize;
}