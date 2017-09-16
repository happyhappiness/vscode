

    /*

     * Now that we are ready to send a response, we need to combine the two

     * header field tables into a single table.  If we don't do this, our

     * later attempts to set or unset a given fieldname might be bypassed.

     */

    if (!is_empty_table(r->err_headers_out))

        r->headers_out = ap_overlay_tables(r->pool, r->err_headers_out,

                                        r->headers_out);



    ap_hard_timeout("send headers", r);



    ap_basic_http_header(r);

