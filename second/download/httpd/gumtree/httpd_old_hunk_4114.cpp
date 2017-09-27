        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
    }
    /* This is all a single brigade, pass with flush flagged */
    return(ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, header_brigade, 1));
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
static apr_status_t proxy_buckets_lifetime_transform(request_rec *r,
        apr_bucket_brigade *from, apr_bucket_brigade *to)
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00964)
                          "Unhandled bucket type of type %s in"
                          " proxy_buckets_lifetime_transform", e->type->name);
            rv = APR_EGENERAL;
        }
    }
    return rv;
}

static
int ap_proxy_http_request(apr_pool_t *p, request_rec *r,
                                   proxy_conn_rec *p_conn, proxy_worker *worker,
                                   proxy_server_conf *conf,
                                   apr_uri_t *uri,
                                   char *url, char *server_portstr)
