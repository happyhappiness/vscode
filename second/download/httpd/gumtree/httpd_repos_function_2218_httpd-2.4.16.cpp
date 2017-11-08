static int mod_proxy_html(apr_pool_t *p, apr_pool_t *p1, apr_pool_t *p2)
{
    seek_meta = ap_pregcomp(p, "<meta[^>]*(http-equiv)[^>]*>",
                            AP_REG_EXTENDED|AP_REG_ICASE);
    seek_content = apr_strmatch_precompile(p, "content", 0);
    memset(&sax, 0, sizeof(htmlSAXHandler));
    sax.startElement = pstartElement;
    sax.endElement = pendElement;
    sax.characters = pcharacters;
    sax.comment = pcomment;
    sax.cdataBlock = pcdata;
    xml2enc_charset = APR_RETRIEVE_OPTIONAL_FN(xml2enc_charset);
    xml2enc_filter = APR_RETRIEVE_OPTIONAL_FN(xml2enc_filter);
    if (!xml2enc_charset) {
        ap_log_perror(APLOG_MARK, APLOG_NOTICE, 0, p2, APLOGNO(01425)
                      "I18n support in mod_proxy_html requires mod_xml2enc. "
                      "Without it, non-ASCII characters in proxied pages are "
                      "likely to display incorrectly.");
    }

    /* old_expr only needs to last the life of the config phase */
    old_expr = ap_rxplus_compile(p1, "s/^(!)?(\\w+)((=)(.+))?$/reqenv('$2')$1$4'$5'/");
    return OK;
}