    if (len > 0) {
        apr_bucket *bucket =
            apr_bucket_transient_create(start, len, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }

    return APR_SUCCESS;
}


/* ssl_io_filter_output() produces one SSL/TLS message per bucket
 * passed down the output filter stack.  This results in a high
