     * Note: this is a teeny bit of overkill since we know there are no
     * '<' or '>' characters, but who cares.
     */
    return apr_xml_quote_string(p, e_uri, 0);
}


/* Write a complete RESPONSE object out as a <DAV:repsonse> xml
   element.  Data is sent into brigade BB, which is auto-flushed into
   OUTPUT filter stack.  Use POOL for any temporary allocations.

   [Presumably the <multistatus> tag has already been written;  this
   routine is shared by dav_send_multistatus and dav_stream_response.]
*/
static void dav_send_one_response(dav_response *response,
                                  apr_bucket_brigade *bb,
                                  ap_filter_t *output,
                                  apr_pool_t *pool)
{
    apr_text *t = NULL;

    if (response->propresult.xmlns == NULL) {
      ap_fputs(output, bb, "<D:response>");
    }
    else {
      ap_fputs(output, bb, "<D:response");
      for (t = response->propresult.xmlns; t; t = t->next) {
        ap_fputs(output, bb, t->text);
      }
      ap_fputc(output, bb, '>');
    }
    
    ap_fputstrs(output, bb,
                DEBUG_CR "<D:href>",
                dav_xml_escape_uri(pool, response->href),
                "</D:href>" DEBUG_CR,
                NULL);
    
    if (response->propresult.propstats == NULL) {
      /* use the Status-Line text from Apache.  Note, this will
       * default to 500 Internal Server Error if first->status
       * is not a known (or valid) status code.
       */
      ap_fputstrs(output, bb,
                  "<D:status>HTTP/1.1 ",
                  ap_get_status_line(response->status),
                  "</D:status>" DEBUG_CR,
                  NULL);
    }
    else {
      /* assume this includes <propstat> and is quoted properly */
      for (t = response->propresult.propstats; t; t = t->next) {
        ap_fputs(output, bb, t->text);
      }
    }
    
    if (response->desc != NULL) {
      /*
       * We supply the description, so we know it doesn't have to
       * have any escaping/encoding applied to it.
       */
      ap_fputstrs(output, bb,
                  "<D:responsedescription>",
                  response->desc,
                  "</D:responsedescription>" DEBUG_CR,
                  NULL);
    }
    
    ap_fputs(output, bb, "</D:response>" DEBUG_CR);
}


/* Factorized helper function: prep request_rec R for a multistatus
   response and write <multistatus> tag into BB, destined for
   R->output_filters.  Use xml NAMESPACES in initial tag, if
   non-NULL. */
static void dav_begin_multistatus(apr_bucket_brigade *bb,
                                  request_rec *r, int status,
                                  apr_array_header_t *namespaces)
{
    /* Set the correct status and Content-Type */
    r->status = status;
    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    /* Send the headers and actual multistatus response now... */
    ap_fputs(r->output_filters, bb, DAV_XML_HEADER DEBUG_CR
             "<D:multistatus xmlns:D=\"DAV:\"");

    if (namespaces != NULL) {
       int i;

       for (i = namespaces->nelts; i--; ) {
           ap_fprintf(r->output_filters, bb, " xmlns:ns%d=\"%s\"", i,
                      APR_XML_GET_URI_ITEM(namespaces, i));
       }
    }

    ap_fputs(r->output_filters, bb, ">" DEBUG_CR);
}


static void dav_send_multistatus(request_rec *r, int status,
                                 dav_response *first,
                                 apr_array_header_t *namespaces)
{
    apr_pool_t *subpool;
    apr_bucket_brigade *bb = apr_brigade_create(r->pool,
                                                r->connection->bucket_alloc);

    dav_begin_multistatus(bb, r, status, namespaces);

    apr_pool_create(&subpool, r->pool);

    for (; first != NULL; first = first->next) {
      apr_pool_clear(subpool);
      dav_send_one_response(first, bb, r->output_filters, subpool);
    }
    apr_pool_destroy(subpool);

    ap_fputs(r->output_filters, bb, "</D:multistatus>" DEBUG_CR);
    ap_filter_flush(bb, r->output_filters);
}

/*
 * dav_log_err()
 *
 * Write error information to the log.
