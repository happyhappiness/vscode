static int ap_parse_request_form(request_rec * r, ap_filter_t * f,
                                 apr_array_header_t ** ptr,
                                 apr_size_t num, apr_size_t size)
{
    apr_bucket_brigade *bb = NULL;
    int seen_eos = 0;
    char buffer[HUGE_STRING_LEN + 1];
    const char *ct;
    apr_size_t offset = 0;
    ap_form_type_t state = FORM_NAME, percent = FORM_NORMAL;
    ap_form_pair_t *pair = NULL;
    apr_array_header_t *pairs = apr_array_make(r->pool, 4, sizeof(ap_form_pair_t));

    char hi = 0;
    char low = 0;

    *ptr = pairs;

    /* sanity check - we only support forms for now */
    ct = apr_table_get(r->headers_in, "Content-Type");
    if (!ct || strcmp("application/x-www-form-urlencoded", ct)) {
        return ap_discard_request_body(r);
    }

    if (!f) {
        f = r->input_filters;
    }

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    do {
        apr_bucket *bucket = NULL, *last = NULL;

        int rv = ap_get_brigade(f, bb, AP_MODE_READBYTES,
                                APR_BLOCK_READ, HUGE_STRING_LEN);
        if (rv != APR_SUCCESS) {
            apr_brigade_destroy(bb);
            return (rv == AP_FILTER_ERROR) ? rv : HTTP_BAD_REQUEST;
        }

        for (bucket = APR_BRIGADE_FIRST(bb);
             bucket != APR_BRIGADE_SENTINEL(bb);
             last = bucket, bucket = APR_BUCKET_NEXT(bucket)) {
            const char *data;
            apr_size_t len, slide;

            if (last) {
                apr_bucket_delete(last);
            }
            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }
            if (bucket->length == 0) {
                continue;
            }

            rv = apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                apr_brigade_destroy(bb);
                return HTTP_BAD_REQUEST;
            }

            slide = len;
            while (state != FORM_ABORT && slide-- > 0 && size >= 0 && num != 0) {
                char c = *data++;
                if ('+' == c) {
                    c = ' ';
                }
                else if ('&' == c) {
                    state = FORM_AMP;
                }
                if ('%' == c) {
                    percent = FORM_PERCENTA;
                    continue;
                }
                if (FORM_PERCENTA == percent) {
                    if (c >= 'a') {
                        hi = c - 'a' + 10;
                    }
                    else if (c >= 'A') {
                        hi = c - 'A' + 10;
                    }
                    else if (c >= '0') {
                        hi = c - '0';
                    }
                    hi = hi << 4;
                    percent = FORM_PERCENTB;
                    continue;
                }
                if (FORM_PERCENTB == percent) {
                    if (c >= 'a') {
                        low = c - 'a' + 10;
                    }
                    else if (c >= 'A') {
                        low = c - 'A' + 10;
                    }
                    else if (c >= '0') {
                        low = c - '0';
                    }
                    c = low | hi;
                    percent = FORM_NORMAL;
                }
                switch (state) {
                case FORM_AMP:
                    if (pair) {
                        const char *tmp = apr_pmemdup(r->pool, buffer, offset);
                        apr_bucket *b = apr_bucket_pool_create(tmp, offset, r->pool, r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(pair->value, b);
                    }
                    state = FORM_NAME;
                    pair = NULL;
                    offset = 0;
                    num--;
                    break;
                case FORM_NAME:
                    if (offset < HUGE_STRING_LEN) {
                        if ('=' == c) {
                            buffer[offset] = 0;
                            offset = 0;
                            pair = (ap_form_pair_t *) apr_array_push(pairs);
                            pair->name = apr_pstrdup(r->pool, buffer);
                            pair->value = apr_brigade_create(r->pool, r->connection->bucket_alloc);
                            state = FORM_VALUE;
                        }
                        else {
                            buffer[offset++] = c;
                            size--;
                        }
                    }
                    else {
                        state = FORM_ABORT;
                    }
                    break;
                case FORM_VALUE:
                    if (offset >= HUGE_STRING_LEN) {
                        const char *tmp = apr_pmemdup(r->pool, buffer, offset);
                        apr_bucket *b = apr_bucket_pool_create(tmp, offset, r->pool, r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(pair->value, b);
                        offset = 0;
                    }
                    buffer[offset++] = c;
                    size--;
                    break;
                default:
                    break;
                }
            }

        }

        apr_brigade_cleanup(bb);
    } while (!seen_eos);

    if (FORM_ABORT == state || size < 0 || num == 0) {
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }
    else if (FORM_VALUE == state && pair && offset > 0) {
        const char *tmp = apr_pmemdup(r->pool, buffer, offset);
        apr_bucket *b = apr_bucket_pool_create(tmp, offset, r->pool, r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(pair->value, b);
    }

    return OK;

}