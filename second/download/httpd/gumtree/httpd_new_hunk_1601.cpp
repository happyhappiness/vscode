#include <stdarg.h>
#endif
#if APR_HAVE_UNISTD_H
#include <unistd.h>
#endif

APLOG_USE_MODULE(http);

#define INVALID_CHAR -2

static long get_chunk_size(char *);

typedef struct http_filter_ctx {
    apr_off_t remaining;
    apr_off_t limit;
    apr_off_t limit_used;
    enum {
        BODY_NONE,
        BODY_LENGTH,
        BODY_CHUNK,
        BODY_CHUNK_PART
    } state;
    int eos_sent;
    char chunk_ln[32];
    char *pos;
    apr_off_t linesize;
    apr_bucket_brigade *bb;
} http_ctx_t;

static apr_status_t bail_out_on_error(http_ctx_t *ctx,
                                      ap_filter_t *f,
                                      int http_error)
{
    apr_bucket *e;
    apr_bucket_brigade *bb = ctx->bb;

    apr_brigade_cleanup(bb);
    e = ap_bucket_error_create(http_error,
                               NULL, f->r->pool,
                               f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    e = apr_bucket_eos_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    ctx->eos_sent = 1;
    return ap_pass_brigade(f->r->output_filters, bb);
}

static apr_status_t get_remaining_chunk_line(http_ctx_t *ctx,
                                             apr_bucket_brigade *b,
                                             int linelimit)
{
    apr_status_t rv;
    apr_off_t brigade_length;
    apr_bucket *e;
    const char *lineend;
    apr_size_t len = 0;

    /*
     * As the brigade b should have been requested in mode AP_MODE_GETLINE
     * all buckets in this brigade are already some type of memory
     * buckets (due to the needed scanning for LF in mode AP_MODE_GETLINE)
     * or META buckets.
     */
    rv = apr_brigade_length(b, 0, &brigade_length);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    /* Sanity check. Should never happen. See above. */
    if (brigade_length == -1) {
        return APR_EGENERAL;
    }
    if (!brigade_length) {
        return APR_EAGAIN;
    }
    ctx->linesize += brigade_length;
    if (ctx->linesize > linelimit) {
        return APR_ENOSPC;
    }
    /*
     * As all buckets are already some type of memory buckets or META buckets
     * (see above), we only need to check the last byte in the last data bucket.
     */
    for (e = APR_BRIGADE_LAST(b);
         e != APR_BRIGADE_SENTINEL(b);
         e = APR_BUCKET_PREV(e)) {

        if (APR_BUCKET_IS_METADATA(e)) {
            continue;
        }
        rv = apr_bucket_read(e, &lineend, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (len > 0) {
            break;  /* we got the data we want */
        }
        /* If we got a zero-length data bucket, we try the next one */
    }
    /* We had no data in this brigade */
    if (!len || e == APR_BRIGADE_SENTINEL(b)) {
        return APR_EAGAIN;
    }
    if (lineend[len - 1] != APR_ASCII_LF) {
        return APR_EAGAIN;
    }
    /* Line is complete. So reset ctx->linesize for next round. */
    ctx->linesize = 0;
    return APR_SUCCESS;
}

static apr_status_t get_chunk_line(http_ctx_t *ctx, apr_bucket_brigade *b,
                                   int linelimit)
{
    apr_size_t len;
    int tmp_len;
    apr_status_t rv;

    tmp_len = sizeof(ctx->chunk_ln) - (ctx->pos - ctx->chunk_ln) - 1;
    /* Saveguard ourselves against underflows */
    if (tmp_len < 0) {
        len = 0;
    }
    else {
        len = (apr_size_t) tmp_len;
    }
    /*
     * Check if there is space left in ctx->chunk_ln. If not, then either
     * the chunk size is insane or we have chunk-extensions. Ignore both
     * by discarding the remaining part of the line via
     * get_remaining_chunk_line. Only bail out if the line is too long.
     */
    if (len > 0) {
        rv = apr_brigade_flatten(b, ctx->pos, &len);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        ctx->pos += len;
        ctx->linesize += len;
        *(ctx->pos) = '\0';
        /*
         * Check if we really got a full line. If yes the
         * last char in the just read buffer must be LF.
         * If not advance the buffer and return APR_EAGAIN.
         * We do not start processing until we have the
         * full line.
         */
        if (ctx->pos[-1] != APR_ASCII_LF) {
            /* Check if the remaining data in the brigade has the LF */
            return get_remaining_chunk_line(ctx, b, linelimit);
        }
        /* Line is complete. So reset ctx->pos for next round. */
        ctx->pos = ctx->chunk_ln;
        return APR_SUCCESS;
    }
    return get_remaining_chunk_line(ctx, b, linelimit);
}


/* This is the HTTP_INPUT filter for HTTP requests and responses from
 * proxied servers (mod_proxy).  It handles chunked and content-length
 * bodies.  This can only be inserted/used after the headers
 * are successfully parsed.
 */
apr_status_t ap_http_filter(ap_filter_t *f, apr_bucket_brigade *b,
