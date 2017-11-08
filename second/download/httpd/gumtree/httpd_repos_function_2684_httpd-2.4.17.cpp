static int kept_body_filter_init(ap_filter_t *f)
{
    apr_off_t length = 0;
    request_rec *r = f->r;
    apr_bucket_brigade *kept_body = r->kept_body;

    if (kept_body) {
        apr_table_unset(r->headers_in, "Transfer-Encoding");
        apr_brigade_length(kept_body, 1, &length);
        apr_table_setn(r->headers_in, "Content-Length", apr_off_t_toa(r->pool, length));
    }

    return OK;
}