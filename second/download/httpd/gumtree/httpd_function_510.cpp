static apr_status_t spool_reqbody_cl(apr_pool_t *p,
                                     request_rec *r,
                                     proxy_http_conn_t *p_conn,
                                     conn_rec *origin,
                                     apr_bucket_brigade *header_brigade,
                                     apr_bucket_brigade *input_brigade,
                                     int force_cl)
{
    int seen_eos = 0;
    apr_status_t status;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *body_brigade;
    apr_bucket *e;
    apr_off_t bytes, bytes_spooled = 0, fsize = 0;
    apr_file_t *tmpfile = NULL;

    body_brigade = apr_brigade_create(p, bucket_alloc);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
        /* If this brigade contains EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            seen_eos = 1;

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            apr_bucket_delete(e);
        }

        apr_brigade_length(input_brigade, 1, &bytes);

        if (bytes_spooled + bytes > MAX_MEM_SPOOL) {
            /* can't spool any more in memory; write latest brigade to disk */
            if (tmpfile == NULL) {
                const char *temp_dir;
                char *template;

                status = apr_temp_dir_get(&temp_dir, p);
                if (status != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: search for temporary directory failed");
                    return status;
                }
                apr_filepath_merge(&template, temp_dir,
                                   "modproxy.tmp.XXXXXX",
                                   APR_FILEPATH_NATIVE, p);
                status = apr_file_mktemp(&tmpfile, template, 0, p);
                if (status != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: creation of temporary file in directory %s failed",
                                 temp_dir);
                    return status;
                }
            }
            for (e = APR_BRIGADE_FIRST(input_brigade);
                 e != APR_BRIGADE_SENTINEL(input_brigade);
                 e = APR_BUCKET_NEXT(e)) {
                const char *data;
                apr_size_t bytes_read, bytes_written;

                apr_bucket_read(e, &data, &bytes_read, APR_BLOCK_READ);
                status = apr_file_write_full(tmpfile, data, bytes_read, &bytes_written);
                if (status != APR_SUCCESS) {
                    const char *tmpfile_name;

                    if (apr_file_name_get(&tmpfile_name, tmpfile) != APR_SUCCESS) {
                        tmpfile_name = "(unknown)";
                    }
                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: write to temporary file %s failed",
                                 tmpfile_name);
                    return status;
                }
                AP_DEBUG_ASSERT(bytes_read == bytes_written);
                fsize += bytes_written;
            }
            apr_brigade_cleanup(input_brigade);
        }
        else {
            APR_BRIGADE_CONCAT(body_brigade, input_brigade);
        }
        
        bytes_spooled += bytes;

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return status;
        }
    }

    if (bytes_spooled || force_cl) {
        add_cl(p, bucket_alloc, header_brigade, apr_off_t_toa(p, bytes_spooled));
    }
    terminate_headers(bucket_alloc, header_brigade);
    APR_BRIGADE_CONCAT(header_brigade, body_brigade);
    if (tmpfile) {
        /* For platforms where the size of the file may be larger than
         * that which can be stored in a single bucket (where the
         * length field is an apr_size_t), split it into several
         * buckets: */
        if (sizeof(apr_off_t) > sizeof(apr_size_t)
            && fsize > AP_MAX_SENDFILE) {
            e = apr_bucket_file_create(tmpfile, 0, AP_MAX_SENDFILE, p,
                                       bucket_alloc);
            while (fsize > AP_MAX_SENDFILE) {
                apr_bucket *ce;
                apr_bucket_copy(e, &ce);
                APR_BRIGADE_INSERT_TAIL(header_brigade, ce);
                e->start += AP_MAX_SENDFILE;
                fsize -= AP_MAX_SENDFILE;
            }
            e->length = (apr_size_t)fsize; /* Resize just the last bucket */
        }
        else {
            e = apr_bucket_file_create(tmpfile, 0, (apr_size_t)fsize, p,
                                       bucket_alloc);
        }
        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
    }
    /* This is all a single brigade, pass with flush flagged */
    status = pass_brigade(bucket_alloc, r, p_conn, origin, header_brigade, 1);
    return status;
}