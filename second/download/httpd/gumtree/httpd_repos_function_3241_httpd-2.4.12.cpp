static void fmt_data(unsigned char *buf, const void *vdata, apr_size_t len, apr_size_t *off)
{
    const unsigned char *data = (const unsigned char *)vdata;
    unsigned char *chars;
    unsigned char *hex;
    apr_size_t this_time = 0;

    memset(buf, ' ', LOG_BYTES_BUFFER_SIZE - 1);
    buf[LOG_BYTES_BUFFER_SIZE - 1] = '\0';
    
    chars = buf; /* start character dump here */
    hex   = buf + BYTES_LOGGED_PER_LINE + 1; /* start hex dump here */
    while (*off < len && this_time < BYTES_LOGGED_PER_LINE) {
        unsigned char c = data[*off];

        if (apr_isprint(c)
	    && c != '\\') {  /* backslash will be escaped later, which throws
                              * off the formatting
                              */
            *chars = c;
        }
        else {
            *chars = '.';
        }

        if ((c >> 4) >= 10) {
            *hex = 'a' + ((c >> 4) - 10);
        }
        else {
            *hex = '0' + (c >> 4);
        }

        if ((c & 0x0F) >= 10) {
            *(hex + 1) = 'a' + ((c & 0x0F) - 10);
        }
        else {
            *(hex + 1) = '0' + (c & 0x0F);
        }

        chars += 1;
        hex += 2;
        *off += 1;
        ++this_time;
    }
}