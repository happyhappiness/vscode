    else
        r->proto_num = HTTP_VERSION(1, 0);

    return 1;
}

AP_DECLARE(void) ap_get_mime_headers_core(request_rec *r, apr_bucket_brigade *bb)
{
    char *last_field = NULL;
    apr_size_t last_len = 0;
    apr_size_t alloc_len = 0;
    char *field;
