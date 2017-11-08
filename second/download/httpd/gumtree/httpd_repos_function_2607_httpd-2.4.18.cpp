static void pcharacters(void *ctxt, const xmlChar *uchars, int length)
{
    const char *chars = (const char*) uchars;
    saxctxt *ctx = (saxctxt*) ctxt;
    int i;
    int begin;
    for (begin=i=0; i<length; i++) {
        switch (chars[i]) {
        case '&' : FLUSH; ap_fputs(ctx->f->next, ctx->bb, "&amp;"); break;
        case '<' : FLUSH; ap_fputs(ctx->f->next, ctx->bb, "&lt;"); break;
        case '>' : FLUSH; ap_fputs(ctx->f->next, ctx->bb, "&gt;"); break;
        case '"' : FLUSH; ap_fputs(ctx->f->next, ctx->bb, "&quot;"); break;
        default : break;
        }
    }
    FLUSH;
}