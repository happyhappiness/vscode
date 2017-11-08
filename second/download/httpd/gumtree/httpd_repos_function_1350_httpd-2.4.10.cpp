apr_table_t *cache_merge_headers_out(request_rec *r)
{
    apr_table_t *headers_out;

    headers_out = apr_table_overlay(r->pool, r->headers_out,
                                    r->err_headers_out);
    apr_table_clear(r->err_headers_out);

    if (r->content_type
            && !apr_table_get(headers_out, "Content-Type")) {
        apr_table_setn(headers_out, "Content-Type",
                       ap_make_content_type(r, r->content_type));
    }

    if (r->content_encoding
            && !apr_table_get(headers_out, "Content-Encoding")) {
        apr_table_setn(headers_out, "Content-Encoding",
                       r->content_encoding);
    }

    return headers_out;
}