int h2_io_is_repeatable(h2_io *io) {
    if (io->submitted
        || io->input_consumed > 0 
        || !io->request) {
        /* cannot repeat that. */
        return 0;
    }
    return (!strcmp("GET", io->request->method)
            || !strcmp("HEAD", io->request->method)
            || !strcmp("OPTIONS", io->request->method));
}