static void pcdata(void *ctxt, const xmlChar *uchars, int length)
{
    const char *chars = (const char*) uchars;
    saxctxt *ctx = (saxctxt*) ctxt;
    if (ctx->cfg->extfix) {
        pappend(ctx, chars, length);
    }
    else {
        /* not sure if this should force-flush
         * (i.e. can one cdata section come in multiple calls?)
         */
        AP_fwrite(ctx, chars, length, 0);
    }
}