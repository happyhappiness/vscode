    e = ap_bucket_error_create(HTTP_BAD_GATEWAY, NULL, c->pool,
                               c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(brigade, e);
    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(brigade, e);
}
