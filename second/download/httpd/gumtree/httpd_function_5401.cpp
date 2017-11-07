static void log_xlate_error(ap_filter_t *f, apr_status_t rv)
{
    charset_filter_ctx_t *ctx = f->ctx;
    const char *msg;
    char msgbuf[100];
    apr_size_t len;

    switch(ctx->ees) {
    case EES_LIMIT:
        rv = 0;
        msg = APLOGNO(02193) "xlate filter - a built-in restriction was encountered";
        break;
    case EES_BAD_INPUT:
        rv = 0;
        msg = APLOGNO(02194) "xlate filter - an input character was invalid";
        break;
    case EES_BUCKET_READ:
        rv = 0;
        msg = APLOGNO(02195) "xlate filter - bucket read routine failed";
        break;
    case EES_INCOMPLETE_CHAR:
        rv = 0;
        strcpy(msgbuf, APLOGNO(02196) "xlate filter - incomplete char at end of input - ");
        len = ctx->saved;

        /* We must ensure not to process more than what would fit in the
         * remaining of the destination buffer, including terminating NULL */
        if (len > (sizeof(msgbuf) - strlen(msgbuf) - 1) / 2)
            len = (sizeof(msgbuf) - strlen(msgbuf) - 1) / 2;

        ap_bin2hex(ctx->buf, len, msgbuf + strlen(msgbuf));
        msg = msgbuf;
        break;
    case EES_DOWNSTREAM:
        msg = APLOGNO(02197) "xlate filter - an error occurred in a lower filter";
        break;
    default:
        msg = APLOGNO(02198) "xlate filter - returning error";
    }
    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(02997) "%s", msg);
}