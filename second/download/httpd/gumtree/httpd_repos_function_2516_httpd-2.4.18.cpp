apr_status_t h2_io_out_close(h2_io *io, apr_table_t *trailers)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    if (!io->eos_out) { /* EOS has not been read yet */
        process_trailers(io, trailers);
        if (!io->bbout) {
            io->bbout = apr_brigade_create(io->pool, io->bucket_alloc);
        }
        if (!h2_util_has_eos(io->bbout, -1)) {
            APR_BRIGADE_INSERT_TAIL(io->bbout, 
                                    apr_bucket_eos_create(io->bbout->bucket_alloc));
        }
    }
    return APR_SUCCESS;
}