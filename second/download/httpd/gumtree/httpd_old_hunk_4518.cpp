         */
        status = apr_file_seek(fd, APR_SET, &offset);
        if (status != APR_SUCCESS) {
            return status;
        }
        status = apr_file_read(fd, io->scratch + io->slen, &len);
#if LOG_SCRATCH
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, io->c, APLOGNO(03387)
                      "h2_conn_io(%ld): FILE_to_scratch(%ld)", 
                      io->c->id, (long)len); 
#endif
        if (status != APR_SUCCESS && status != APR_EOF) {
            return status;
        }
        io->slen += len;
    }
    else {
        status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
        if (status == APR_SUCCESS) {
#if LOG_SCRATCH
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03388)
                          "h2_conn_io(%ld): read_to_scratch(%ld)", 
                          io->c->id, (long)b->length); 
#endif
            memcpy(io->scratch+io->slen, data, len);
            io->slen += len;
        }
    }
    return status;
}
