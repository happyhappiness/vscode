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

  parser_error:
    (void) apr_xml_parser_geterror(parser, errbuf, sizeof(errbuf));
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "%s", errbuf);

    /* FALLTHRU */

  read_error:
    /* make sure the parser is terminated */
