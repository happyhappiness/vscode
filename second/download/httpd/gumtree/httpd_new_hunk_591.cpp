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
