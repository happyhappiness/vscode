static apr_status_t simple_io_callback(void *baton, apr_pollfd_t * pfd)
{
    apr_status_t rv = APR_SUCCESS;
    simple_core_t *sc = (simple_core_t *) baton;
    simple_sb_t *sb = pfd->client_data;


    if (sb->type == SIMPLE_PT_CORE_ACCEPT) {
        rv = simple_io_accept(sc, sb);
    }
    else if (sb->type == SIMPLE_PT_CORE_IO) {
        rv = simple_io_event_process(sc, sb);
    }
    else if (sb->type == SIMPLE_PT_USER) {
        /* TODO: */
        abort();
    }
    else {
        abort();
    }

    return rv;
}