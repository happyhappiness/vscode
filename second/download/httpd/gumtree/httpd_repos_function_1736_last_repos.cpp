static void do_emit_plain(request_rec *r, apr_file_t *f)
{
    char buf[AP_IOBUFSIZE + 1];
    int ch;
    apr_size_t i, c, n;
    apr_status_t rv;

    ap_rputs("<pre>\n", r);
    while (!apr_file_eof(f)) {
        do {
            n = sizeof(char) * AP_IOBUFSIZE;
            rv = apr_file_read(f, buf, &n);
        } while (APR_STATUS_IS_EINTR(rv));
        if (n == 0 || rv != APR_SUCCESS) {
            /* ###: better error here? */
            break;
        }
        buf[n] = '\0';
        c = 0;
        while (c < n) {
            for (i = c; i < n; i++) {
                if (buf[i] == '<' || buf[i] == '>' || buf[i] == '&') {
                    break;
                }
            }
            ch = buf[i];
            buf[i] = '\0';
            ap_rputs(&buf[c], r);
            if (ch == '<') {
                ap_rputs("&lt;", r);
            }
            else if (ch == '>') {
                ap_rputs("&gt;", r);
            }
            else if (ch == '&') {
                ap_rputs("&amp;", r);
            }
            c = i + 1;
        }
    }
    ap_rputs("</pre>\n", r);
}