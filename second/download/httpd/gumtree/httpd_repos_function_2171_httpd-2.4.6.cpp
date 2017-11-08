static void pcomment(void *ctxt, const xmlChar *uchars)
{
    const char *chars = (const char*) uchars;
    saxctxt *ctx = (saxctxt*) ctxt;
    if (ctx->cfg->strip_comments)
        return;

    if (ctx->cfg->extfix) {
        pappend(ctx, "<!--", 4);
        pappend(ctx, chars, strlen(chars));
        pappend(ctx, "-->", 3);
    }
    else {
        ap_fputs(ctx->f->next, ctx->bb, "<!--");
        AP_fwrite(ctx, chars, strlen(chars), 1);
        ap_fputs(ctx->f->next, ctx->bb, "-->");
    }
}