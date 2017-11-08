static apr_status_t in_append_eos(h2_io *io, apr_bucket_brigade *bb, 
                                  apr_table_t *trailers)
{
    apr_status_t status = APR_SUCCESS;
    apr_table_t *t = io->request->trailers;

    if (trailers && t && !apr_is_empty_table(trailers)) {
        /* trailers passed in, transfer directly. */
        apr_table_overlap(trailers, t, APR_OVERLAP_TABLES_SET);
        t = NULL;
    }
    
    if (io->request->chunked) {
        if (t && !apr_is_empty_table(t)) {
            /* no trailers passed in, transfer via chunked */
            status = apr_brigade_puts(bb, NULL, NULL, "0\r\n");
            apr_table_do(add_trailer, bb, t, NULL);
            status = apr_brigade_puts(bb, NULL, NULL, "\r\n");
        }
        else {
            status = apr_brigade_puts(bb, NULL, NULL, "0\r\n\r\n");
        }
    }
    append_eos(io, bb);
    return status;
}