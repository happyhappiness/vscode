                      ((float)io->cooldown_usecs/APR_USEC_PER_SEC));
    }

    return APR_SUCCESS;
}

#define LOG_SCRATCH 0

static void append_scratch(h2_conn_io *io) 
{
    if (io->scratch && io->slen > 0) {
        apr_bucket *b = apr_bucket_heap_create(io->scratch, io->slen,
                                               apr_bucket_free,
                                               io->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
#if LOG_SCRATCH
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03386)
                      "h2_conn_io(%ld): append_scratch(%ld)", 
                      io->c->id, (long)io->slen);
#endif
        io->scratch = NULL;
        io->slen = io->ssize = 0;
    }
}

static apr_size_t assure_scratch_space(h2_conn_io *io) {
    apr_size_t remain = io->ssize - io->slen; 
    if (io->scratch && remain == 0) {
        append_scratch(io);
    }
    if (!io->scratch) {
        /* we control the size and it is larger than what buckets usually
         * allocate. */
        io->scratch = apr_bucket_alloc(io->write_size, io->c->bucket_alloc);
        io->ssize = io->write_size;
        io->slen = 0;
        remain = io->ssize;
    }
    return remain;
}
    
static apr_status_t read_to_scratch(h2_conn_io *io, apr_bucket *b)
{
    apr_status_t status;
    const char *data;
    apr_size_t len;
    
    if (!b->length) {
        return APR_SUCCESS;
    }
    
    AP_DEBUG_ASSERT(b->length <= (io->ssize - io->slen));
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

static void check_write_size(h2_conn_io *io) 
{
    if (io->write_size > WRITE_SIZE_INITIAL 
        && (io->cooldown_usecs > 0)
        && (apr_time_now() - io->last_write) >= io->cooldown_usecs) {
        /* long time not written, reset write size */
        io->write_size = WRITE_SIZE_INITIAL;
        io->bytes_written = 0;
