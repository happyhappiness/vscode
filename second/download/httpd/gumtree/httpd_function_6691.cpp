static void dump_header_to_log(request_rec *r, unsigned char fheader[],
                               apr_size_t length)
{
#ifdef FCGI_DUMP_HEADERS
    apr_size_t posn = 0;
    char asc_line[20];
    char hex_line[60];
    int i = 0;

    memset(asc_line, 0, sizeof(asc_line));
    memset(hex_line, 0, sizeof(hex_line));

    while (posn < length) {
        unsigned char c = fheader[posn];

        if (i >= 20) {
            i = 0;

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01064)
                          "HEADER: %s %s", asc_line, hex_line);

            memset(asc_line, 0, sizeof(asc_line));
            memset(hex_line, 0, sizeof(hex_line));
        }

        if (isprint(c)) {
            asc_line[i] = c;
        }
        else {
            asc_line[i] = '.';
        }

        if ((c >> 4) >= 10) {
            hex_line[i * 3] = 'a' + ((c >> 4) - 10);
        }
        else {
            hex_line[i * 3] = '0' + (c >> 4);
        }

        if ((c & 0x0F) >= 10) {
            hex_line[i * 3 + 1] = 'a' + ((c & 0x0F) - 10);
        }
        else {
            hex_line[i * 3 + 1] = '0' + (c & 0xF);
        }

        hex_line[i * 3 + 2] = ' ';

        i++;
        posn++;
    }

    if (i != 1) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01065) "HEADER: %s %s",
                      asc_line, hex_line);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01066) "HEADER: -EOH-");
#endif
}