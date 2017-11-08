void h2_io_set_response(h2_io *io, h2_response *response) 
{
    AP_DEBUG_ASSERT(io->pool);
    AP_DEBUG_ASSERT(response);
    AP_DEBUG_ASSERT(!io->response);
    /* we used to clone the response into the io->pool. But
     * we have much tighter control over the EOR bucket nowadays,
     * so just use the instance given */
    io->response = response;
    if (response->rst_error) {
        h2_io_rst(io, response->rst_error);
    }
    else if (response->content_length == 0) {
        io->eos_out = 1;
    }
}