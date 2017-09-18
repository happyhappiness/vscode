     * Note: this is a teeny bit of overkill since we know there are no
     * '<' or '>' characters, but who cares.
     */
    return apr_xml_quote_string(p, e_uri, 0);
}

static void dav_send_multistatus(request_rec *r, int status,
                                 dav_response *first,
                                 apr_array_header_t *namespaces)
{
    /* Set the correct status and Content-Type */
    r->status = status;
    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    /* Send the headers and actual multistatus response now... */
    ap_rputs(DAV_XML_HEADER DEBUG_CR
             "<D:multistatus xmlns:D=\"DAV:\"", r);

    if (namespaces != NULL) {
       int i;

       for (i = namespaces->nelts; i--; ) {
           ap_rprintf(r, " xmlns:ns%d=\"%s\"", i,
                      APR_XML_GET_URI_ITEM(namespaces, i));
       }
    }

    /* ap_rputc('>', r); */
    ap_rputs(">" DEBUG_CR, r);

    for (; first != NULL; first = first->next) {
        apr_text *t;

        if (first->propresult.xmlns == NULL) {
            ap_rputs("<D:response>", r);
        }
        else {
            ap_rputs("<D:response", r);
            for (t = first->propresult.xmlns; t; t = t->next) {
                ap_rputs(t->text, r);
            }
            ap_rputc('>', r);
        }

        ap_rputs(DEBUG_CR "<D:href>", r);
        ap_rputs(dav_xml_escape_uri(r->pool, first->href), r);
        ap_rputs("</D:href>" DEBUG_CR, r);

        if (first->propresult.propstats == NULL) {
            /* use the Status-Line text from Apache.  Note, this will
             * default to 500 Internal Server Error if first->status
             * is not a known (or valid) status code.
             */
            ap_rprintf(r,
                       "<D:status>HTTP/1.1 %s</D:status>" DEBUG_CR,
                       ap_get_status_line(first->status));
        }
        else {
            /* assume this includes <propstat> and is quoted properly */
            for (t = first->propresult.propstats; t; t = t->next) {
                ap_rputs(t->text, r);
            }
        }

        if (first->desc != NULL) {
            /*
             * We supply the description, so we know it doesn't have to
             * have any escaping/encoding applied to it.
             */
            ap_rputs("<D:responsedescription>", r);
            ap_rputs(first->desc, r);
            ap_rputs("</D:responsedescription>" DEBUG_CR, r);
        }

        ap_rputs("</D:response>" DEBUG_CR, r);
    }

    ap_rputs("</D:multistatus>" DEBUG_CR, r);
}

/*
 * dav_log_err()
 *
 * Write error information to the log.
