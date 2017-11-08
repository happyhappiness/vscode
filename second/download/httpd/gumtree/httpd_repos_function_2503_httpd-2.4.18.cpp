void h2_io_set_response(h2_io *io, h2_response *response) 
{
    AP_DEBUG_ASSERT(io->pool);
    AP_DEBUG_ASSERT(response);
    AP_DEBUG_ASSERT(!io->response);
    io->response = h2_response_clone(io->pool, response);
    if (response->rst_error) {
        h2_io_rst(io, response->rst_error);
    }
}