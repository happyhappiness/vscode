static apr_text * dav_failed_proppatch(apr_pool_t *p,
                                      apr_array_header_t *prop_ctx)
{
    apr_text_header hdr = { 0 };
    int i = prop_ctx->nelts;
    dav_prop_ctx *ctx = (dav_prop_ctx *)prop_ctx->elts;
    dav_error *err424_set = NULL;
    dav_error *err424_delete = NULL;
    const char *s;

    /* ### might be nice to sort by status code and description */

    for ( ; i-- > 0; ++ctx ) {
        apr_text_append(p, &hdr,
                        "<D:propstat>" DEBUG_CR
                        "<D:prop>");
        apr_text_append(p, &hdr, apr_xml_empty_elem(p, ctx->prop));
        apr_text_append(p, &hdr, "</D:prop>" DEBUG_CR);

        if (ctx->err == NULL) {
            /* nothing was assigned here yet, so make it a 424 */

            if (ctx->operation == DAV_PROP_OP_SET) {
                if (err424_set == NULL)
                    err424_set = dav_new_error(p, HTTP_FAILED_DEPENDENCY, 0, 0,
                                               "Attempted DAV:set operation "
                                               "could not be completed due "
                                               "to other errors.");
                ctx->err = err424_set;
            }
            else if (ctx->operation == DAV_PROP_OP_DELETE) {
                if (err424_delete == NULL)
                    err424_delete = dav_new_error(p, HTTP_FAILED_DEPENDENCY, 0, 0,
                                                  "Attempted DAV:remove "
                                                  "operation could not be "
                                                  "completed due to other "
                                                  "errors.");
                ctx->err = err424_delete;
            }
        }

        s = apr_psprintf(p,
                         "<D:status>"
                         "HTTP/1.1 %d (status)"
                         "</D:status>" DEBUG_CR,
                         ctx->err->status);
        apr_text_append(p, &hdr, s);

        /* ### we should use compute_desc if necessary... */
        if (ctx->err->desc != NULL) {
            apr_text_append(p, &hdr, "<D:responsedescription>" DEBUG_CR);
            apr_text_append(p, &hdr, ctx->err->desc);
            apr_text_append(p, &hdr, "</D:responsedescription>" DEBUG_CR);
        }

        apr_text_append(p, &hdr, "</D:propstat>" DEBUG_CR);
    }

    return hdr.first;
}