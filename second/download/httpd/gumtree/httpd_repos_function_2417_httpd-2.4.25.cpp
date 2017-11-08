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