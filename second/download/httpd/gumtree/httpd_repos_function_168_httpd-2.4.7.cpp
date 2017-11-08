static int
dialup_send_pulse(dialup_baton_t *db)
{
    int status;
    apr_off_t len = 0;
    apr_size_t bytes_sent = 0;

    while (!APR_BRIGADE_EMPTY(db->bb) && bytes_sent < db->bytes_per_second) {
        apr_bucket *e;

        if (db->r->connection->aborted) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        status = apr_brigade_partition(db->bb, db->bytes_per_second, &e);

        if (status != APR_SUCCESS && status != APR_INCOMPLETE) {
            /* XXXXXX: Log me. */
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        if (e != APR_BRIGADE_SENTINEL(db->bb)) {
            apr_bucket *f;
            apr_bucket *b = APR_BUCKET_PREV(e);
            f = APR_RING_FIRST(&db->bb->list);
            APR_RING_UNSPLICE(f, b, link);
            APR_RING_SPLICE_HEAD(&db->tmpbb->list, f, b, apr_bucket, link);
        }
        else {
            APR_BRIGADE_CONCAT(db->tmpbb, db->bb);
        }

        e = apr_bucket_flush_create(db->r->connection->bucket_alloc);

        APR_BRIGADE_INSERT_TAIL(db->tmpbb, e);

        apr_brigade_length(db->tmpbb, 1, &len);
        bytes_sent += len;
        status = ap_pass_brigade(db->r->output_filters, db->tmpbb);

        apr_brigade_cleanup(db->tmpbb);

        if (status != OK) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, db->r, APLOGNO(01867)
                          "dialup: pulse: ap_pass_brigade failed:");
            return status;
        }
    }

    if (APR_BRIGADE_EMPTY(db->bb)) {
        return DONE;
    }
    else {
        return SUSPENDED;
    }
}