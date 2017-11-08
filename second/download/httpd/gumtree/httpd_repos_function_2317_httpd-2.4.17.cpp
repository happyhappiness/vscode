apr_status_t h2_conn_io_init(h2_conn_io *io, conn_rec *c)
{
    io->connection = c;
    io->input = apr_brigade_create(c->pool, c->bucket_alloc);
    io->output = apr_brigade_create(c->pool, c->bucket_alloc);
    io->buflen = 0;
    /* That is where we start with, 
     * see https://issues.apache.org/jira/browse/TS-2503 */
    io->write_size = WRITE_SIZE_INITIAL; 
    io->last_write = 0;
    io->buffer_output = h2_h2_is_tls(c);

    /* Currently we buffer only for TLS output. The reason this gives
     * improved performance is that buckets send to the mod_ssl network
     * filter will be encrypted in chunks. There is a special filter
     * that tries to aggregate data, but that does not work well when
     * bucket sizes alternate between tiny frame headers and large data
     * chunks.
     */
    if (io->buffer_output) {
        io->bufsize = WRITE_BUFFER_SIZE;
        io->buffer = apr_pcalloc(c->pool, io->bufsize);
    }
    else {
        io->bufsize = 0;
    }
    
    return APR_SUCCESS;
}