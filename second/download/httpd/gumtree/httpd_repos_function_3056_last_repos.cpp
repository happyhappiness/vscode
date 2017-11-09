static const char *get_content_encoding(request_rec *r)
{
    const char *encoding;

    encoding = apr_table_get(r->headers_out, "Content-Encoding");
    if (encoding) {
        const char *err_enc;

        err_enc = apr_table_get(r->err_headers_out, "Content-Encoding");
        if (err_enc) {
            encoding = apr_pstrcat(r->pool, encoding, ",", err_enc, NULL);
        }
    }
    else {
        encoding = apr_table_get(r->err_headers_out, "Content-Encoding");
    }

    if (r->content_encoding) {
        encoding = encoding ? apr_pstrcat(r->pool, encoding, ",",
                                          r->content_encoding, NULL)
                            : r->content_encoding;
    }

    return encoding;
}