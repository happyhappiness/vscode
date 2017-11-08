static void deflate_check_etag(request_rec *r, const char *transform)
{
    const char *etag = apr_table_get(r->headers_out, "ETag");
    if (etag && (((etag[0] != 'W') && (etag[0] !='w')) || (etag[1] != '/'))) {
        apr_table_set(r->headers_out, "ETag",
                      apr_pstrcat(r->pool, etag, "-", transform, NULL));
    }
}