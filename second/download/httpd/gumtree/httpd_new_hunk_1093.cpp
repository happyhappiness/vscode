    e = ap_bucket_error_create(HTTP_BAD_GATEWAY, NULL, c->pool,
                               c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(brigade, e);
    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(brigade, e);
}

/*
 * Transform buckets from one bucket allocator to another one by creating a
 * transient bucket for each data bucket and let it use the data read from
 * the old bucket. Metabuckets are transformed by just recreating them.
 * Attention: Currently only the following bucket types are handled:
 *
 * All data buckets
 * FLUSH
 * EOS
 *
 * If an other bucket type is found its type is logged as a debug message
 * and APR_EGENERAL is returned.
 */
PROXY_DECLARE(apr_status_t)
ap_proxy_buckets_lifetime_transform(request_rec *r, apr_bucket_brigade *from,
                                    apr_bucket_brigade *to)
{
    apr_bucket *e;
    apr_bucket *new;
    const char *data;
    apr_size_t bytes;
    apr_status_t rv = APR_SUCCESS;

    apr_brigade_cleanup(to);
    for (e = APR_BRIGADE_FIRST(from);
         e != APR_BRIGADE_SENTINEL(from);
         e = APR_BUCKET_NEXT(e)) {
        if (!APR_BUCKET_IS_METADATA(e)) {
            apr_bucket_read(e, &data, &bytes, APR_BLOCK_READ);
            new = apr_bucket_transient_create(data, bytes, r->connection->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(to, new);
        }
        else if (APR_BUCKET_IS_FLUSH(e)) {
            new = apr_bucket_flush_create(r->connection->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(to, new);
        }
        else if (APR_BUCKET_IS_EOS(e)) {
            new = apr_bucket_eos_create(r->connection->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(to, new);
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: Unhandled bucket type of type %s in"
                          " ap_proxy_buckets_lifetime_transform", e->type->name);
            rv = APR_EGENERAL;
        }
    }
    return rv;
}

