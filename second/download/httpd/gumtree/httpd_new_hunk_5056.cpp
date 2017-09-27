    if (field > 1 || i > 9)
        put_int_flush_right(r, i / 10, field - 1);
    if (i) {
        if (r)
            ap_rputc('0' + i % 10, r);
        else
            apr_file_putc((char)('0' + i % 10), out);
    }
    else {
        if (r)
            ap_rputs("&nbsp;", r);
        else
            apr_file_printf(out, " ");
