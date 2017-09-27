                      ((float)io->cooldown_usecs/APR_USEC_PER_SEC));
    }

    return APR_SUCCESS;
}

static void append_scratch(h2_conn_io *io) 
{
    if (io->scratch && io->slen > 0) {
        apr_bucket *b = apr_bucket_heap_create(io->scratch, io->slen,
                                               apr_bucket_free,
                                               io->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
        io->scratch = NULL;
        io->slen = io->ssize = 0;
    }
}

static apr_size_t assure_scratch_space(h2_conn_io *io) {
