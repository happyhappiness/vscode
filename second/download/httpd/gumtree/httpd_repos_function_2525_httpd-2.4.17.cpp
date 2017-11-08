static void pendElement(void *ctxt, const xmlChar *uname)
{
    saxctxt *ctx = (saxctxt*) ctxt;
    const char *name = (const char*) uname;
    const htmlElemDesc* desc = htmlTagLookup(uname);

    if ((ctx->cfg->doctype == fpi_html) || (ctx->cfg->doctype == fpi_xhtml)) {
        /* enforce html */
        if (!desc || desc->depr)
            return;
    
    }
    else if ((ctx->cfg->doctype == fpi_html)
             || (ctx->cfg->doctype == fpi_xhtml)) {
        /* enforce html legacy */
        if (!desc)
            return;
    }
    /* TODO - implement HTML "allowed here" using the stack */
    /* nah.  Keeping the stack is too much overhead */

    if (ctx->offset > 0) {
        dump_content(ctx);
        ctx->offset = 0;        /* having dumped it, we can re-use the memory */
    }
    if (!desc || !desc->empty) {
        ap_fprintf(ctx->f->next, ctx->bb, "</%s>", name);
    }
}