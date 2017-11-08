void apr_pollset_drain_wakeup_pipe(apr_pollset_t *pollset)
{
    char rb[512];
    apr_size_t nr = sizeof(rb);

    while (apr_file_read(pollset->wakeup_pipe[0], rb, &nr) == APR_SUCCESS) {
        /* Although we write just one byte to the other end of the pipe
         * during wakeup, multiple threads could call the wakeup.
         * So simply drain out from the input side of the pipe all
         * the data.
         */
        if (nr != sizeof(rb))
            break;
    }
}