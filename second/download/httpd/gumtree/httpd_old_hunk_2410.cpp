

    rr->content_type = CGI_MAGIC_TYPE;



    /* Run it. */



    rr_status = ap_run_sub_req(rr);

    if (is_HTTP_REDIRECT(rr_status)) {

        const char *location = ap_table_get(rr->headers_out, "Location");

        location = ap_escape_html(rr->pool, location);

        ap_rvputs(r, "<A HREF=\"", location, "\">", location, "</A>", NULL);

    }



    ap_destroy_sub_req(rr);

