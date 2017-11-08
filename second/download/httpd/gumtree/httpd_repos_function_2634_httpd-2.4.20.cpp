static void append_eos(h2_io *io, apr_bucket_brigade *bb)
{
    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_eos_create(io->bucket_alloc));
}