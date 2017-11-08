static apr_text * dav_success_proppatch(apr_pool_t *p, apr_array_header_t *prop_ctx)
{
    apr_text_header hdr = { 0 };
    int i = prop_ctx->nelts;
    dav_prop_ctx *ctx = (dav_prop_ctx *)prop_ctx->elts;

    /*
     * ### we probably need to revise the way we assemble the response...
     * ### this code assumes everything will return status==200.
     */

    apr_text_append(p, &hdr,
                    "<D:propstat>" DEBUG_CR
                    "<D:prop>" DEBUG_CR);

    for ( ; i-- > 0; ++ctx ) {
        apr_text_append(p, &hdr, apr_xml_empty_elem(p, ctx->prop));
    }

    apr_text_append(p, &hdr,
                   "</D:prop>" DEBUG_CR
                   "<D:status>HTTP/1.1 200 OK</D:status>" DEBUG_CR
                   "</D:propstat>" DEBUG_CR);

    return hdr.first;
}