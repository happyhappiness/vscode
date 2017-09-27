        return rv;
    }

    bytes_in_brigade = 0;
    non_file_bytes_in_brigade = 0;
    eor_buckets_in_brigade = 0;
    morphing_bucket_in_brigade = 0;

    for (bucket = APR_BRIGADE_FIRST(bb); bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        next = APR_BUCKET_NEXT(bucket);

        if (!APR_BUCKET_IS_METADATA(bucket)) {
            if (bucket->length == (apr_size_t)-1) {
                /*
                 * A setaside of morphing buckets would read everything into
                 * memory. Instead, we will flush everything up to and
                 * including this bucket.
                 */
                morphing_bucket_in_brigade = 1;
            }
            else {
                bytes_in_brigade += bucket->length;
                if (!APR_BUCKET_IS_FILE(bucket))
                    non_file_bytes_in_brigade += bucket->length;
            }
        }
        else if (AP_BUCKET_IS_EOR(bucket)) {
            eor_buckets_in_brigade++;
        }

        if (APR_BUCKET_IS_FLUSH(bucket)
            || non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER
            || morphing_bucket_in_brigade
            || eor_buckets_in_brigade > MAX_REQUESTS_IN_PIPELINE) {
            /* this segment of the brigade MUST be sent before returning. */

            if (APLOGctrace6(c)) {
                char *reason = APR_BUCKET_IS_FLUSH(bucket) ?
                               "FLUSH bucket" :
                               (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) ?
                               "THRESHOLD_MAX_BUFFER" :
                               morphing_bucket_in_brigade ? "morphing bucket" :
                               "MAX_REQUESTS_IN_PIPELINE";
                ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, c,
                              "core_output_filter: flushing because of %s",
                              reason);
            }
            /*
