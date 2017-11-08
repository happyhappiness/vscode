static void process_trailers(h2_io *io, apr_table_t *trailers)
{
    if (trailers && io->response) {
        h2_response_set_trailers(io->response, 
                                 apr_table_clone(io->pool, trailers));
    }
}