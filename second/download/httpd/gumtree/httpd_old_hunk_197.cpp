#define READ_BLOCKSIZE 2048


AP_DECLARE(int) ap_xml_parse_input(request_rec * r, apr_xml_doc **pdoc)
{
    apr_xml_parser *parser;
    int result;
    apr_status_t status;
    char errbuf[200];

    if ((result = ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK)) != OK)
        return result;

    if (r->remaining == 0) {
        *pdoc = NULL;
        return OK;
    }

    parser = apr_xml_parser_create(r->pool);

    if (ap_should_client_block(r)) {
        long len;
        char *buffer;
        apr_size_t total_read = 0;
        apr_size_t limit_xml_body = ap_get_limit_xml_body(r);

        /* allocate our working buffer */
        buffer = apr_palloc(r->pool, READ_BLOCKSIZE);

        /* read the body, stuffing it into the parser */
        while ((len = ap_get_client_block(r, buffer, READ_BLOCKSIZE)) > 0) {
            total_read += len;
            if (limit_xml_body && total_read > limit_xml_body) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "XML request body is larger than the configured "
                              "limit of %lu", (unsigned long)limit_xml_body);
                goto read_error;
            }

            status = apr_xml_parser_feed(parser, buffer, len);
            if (status)
                goto parser_error;
        }
        if (len == -1) {
            /* ap_get_client_block() has logged an error */
            goto read_error;
        }
    }

    /* tell the parser that we're done */
    status = apr_xml_parser_done(parser, pdoc);
    if (status) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "XML parser error (at end). status=%d", status);
        return HTTP_BAD_REQUEST;
    }

    return OK;
