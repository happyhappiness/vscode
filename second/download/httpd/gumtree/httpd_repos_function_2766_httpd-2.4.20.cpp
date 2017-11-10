static apr_status_t proxy_html_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    apr_bucket* b;
    meta *m = NULL;
    xmlCharEncoding enc;
    const char *buf = 0;
    apr_size_t bytes = 0;
#ifndef USE_OLD_LIBXML2
    int xmlopts = XML_PARSE_RECOVER | XML_PARSE_NONET |
                  XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING;
#endif

    saxctxt *ctxt = check_filter_init(f);
    if (!ctxt)
        return ap_pass_brigade(f->next, bb);
    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b)) {
        if (APR_BUCKET_IS_METADATA(b)) {
            if (APR_BUCKET_IS_EOS(b)) {
                if (ctxt->parser != NULL) {
                    consume_buffer(ctxt, buf, 0, 1);
                }
                APR_BRIGADE_INSERT_TAIL(ctxt->bb,
                apr_bucket_eos_create(ctxt->bb->bucket_alloc));
                ap_pass_brigade(ctxt->f->next, ctxt->bb);
            }
            else if (APR_BUCKET_IS_FLUSH(b)) {
                /* pass on flush, except at start where it would cause
                 * headers to be sent before doc sniffing
                 */
                if (ctxt->parser != NULL) {
                    ap_fflush(ctxt->f->next, ctxt->bb);
                }
            }
        }
        else if (apr_bucket_read(b, &buf, &bytes, APR_BLOCK_READ)
                 == APR_SUCCESS) {
            if (ctxt->parser == NULL) {
                const char *cenc;
                if (!xml2enc_charset ||
                    (xml2enc_charset(f->r, &enc, &cenc) != APR_SUCCESS)) {
                    if (!xml2enc_charset)
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r, APLOGNO(01422)
                     "No i18n support found.  Install mod_xml2enc if required");
                    enc = XML_CHAR_ENCODING_NONE;
                    ap_set_content_type(f->r, "text/html;charset=utf-8");
                }
                else {
                    /* if we wanted a non-default charset_out, insert the
                     * xml2enc filter now that we've sniffed it
                     */
                    if (ctxt->cfg->charset_out && xml2enc_filter) {
                        if (*ctxt->cfg->charset_out != '*')
                            cenc = ctxt->cfg->charset_out;
                        xml2enc_filter(f->r, cenc, ENCIO_OUTPUT);
                        ap_set_content_type(f->r,
                                            apr_pstrcat(f->r->pool,
                                                        "text/html;charset=",
                                                        cenc, NULL));
                    }
                    else /* Normal case, everything worked, utf-8 output */
                        ap_set_content_type(f->r, "text/html;charset=utf-8");
                }

                ap_fputs(f->next, ctxt->bb, ctxt->cfg->doctype);
                ctxt->parser = htmlCreatePushParserCtxt(&sax, ctxt, buf,
                                                        4, 0, enc);
                buf += 4;
                bytes -= 4;
                if (ctxt->parser == NULL) {
                    apr_status_t rv = ap_pass_brigade(f->next, bb);
                    ap_remove_output_filter(f);
                    return rv;
                }
                apr_pool_cleanup_register(f->r->pool, ctxt->parser,
                                          (int(*)(void*))htmlFreeParserCtxt,
                                          apr_pool_cleanup_null);
#ifndef USE_OLD_LIBXML2
                if (xmlopts = xmlCtxtUseOptions(ctxt->parser, xmlopts), xmlopts)
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r, APLOGNO(01423)
                                  "Unsupported parser opts %x", xmlopts);
#endif
                if (ctxt->cfg->metafix)
                    m = metafix(f->r, buf);
                if (m) {
                    consume_buffer(ctxt, buf, m->start, 0);
                    consume_buffer(ctxt, buf+m->end, bytes-m->end, 0);
                }
                else {
                    consu