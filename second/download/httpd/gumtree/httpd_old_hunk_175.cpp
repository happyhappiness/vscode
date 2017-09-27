
    if (r_accept_enc) {
        apr_table_setn(hdrs, "Accept-Encoding", r_accept_enc);
    }

    if (emit_amble) {
        emit_preamble(r, title);
    }
    if (emit_H1) {
        ap_rvputs(r, "<h1>Index of ", title, "</h1>\n", NULL);
    }
    if (rr != NULL) {
        ap_destroy_sub_req(rr);
