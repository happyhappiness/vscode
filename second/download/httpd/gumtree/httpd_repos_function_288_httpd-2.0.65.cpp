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