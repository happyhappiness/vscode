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