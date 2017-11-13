static apr_status_t read_to_scratch(h2_conn_io *io, apr_bucket *b)
{
    apr_status_t status;
    const char *data;
    apr_size_t len;
    
    if (!b->length) {
        return APR_SUCCESS;
    }
    
    ap_assert(b->length <= (io->ssize - io->slen));
    if (APR_BUCKET_IS_FILE(b)) {
        apr_bucket_file *f = (apr_bucket_file *)b->data;
        apr_file_t *fd = f->fd;
        apr_off_t offset = b->start;
        apr_size_t len = b->length;
        
        /* file buckets will either mmap (which we do not want) or
         * read 8000 byte chunks and split themself. However, we do
         * know *exactly* how many bytes we need where.
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