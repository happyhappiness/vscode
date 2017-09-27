
    memset(asc_line, 0, sizeof(asc_line));
    memset(hex_line, 0, sizeof(hex_line));

    while (posn < length) {
        unsigned char c = fheader[posn]; 

        if (i >= 20) {
            i = 0;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "HEADER: %s %s", asc_line, hex_line);
