static void clone_headers_no_body(request_rec *rnew,
                                  const request_rec *r)
{
    rnew->headers_in = apr_table_copy(rnew->pool, r->headers_in);
    apr_table_unset(rnew->headers_in, "Content-Encoding");
    apr_table_unset(rnew->headers_in, "Content-Language");
    apr_table_unset(rnew->headers_in, "Content-Length");
    apr_table_unset(rnew->headers_in, "Content-Location");
    apr_table_unset(rnew->headers_in, "Content-MD5");
    apr_table_unset(rnew->headers_in, "Content-Range");
    apr_table_unset(rnew->headers_in, "Content-Type");
    apr_table_unset(rnew->headers_in, "Expires");
    apr_table_unset(rnew->headers_in, "Last-Modified");
    apr_table_unset(rnew->headers_in, "Transfer-Encoding");
}