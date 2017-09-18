
    /* ### I really don't think this is needed; gotta test */
    r->status_line = ap_get_status_line(status);

    ap_set_content_type(r, "text/html");

    /* since we're returning DONE, ensure the request body is consumed. */
    (void) ap_discard_request_body(r);

    /* begin the response now... */
    ap_rvputs(r,
              DAV_RESPONSE_BODY_1,
              r->status_line,
              DAV_RESPONSE_BODY_2,
              &r->status_line[4],
