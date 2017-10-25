static int
fill_buffer(URL_FILE *file,int want,int waittime)
{
    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd;
    struct timeval timeout;
    int rc;

    /* only attempt to fill buffer if transactions still running and buffer
     * doesnt exceed required size already
     */
    if((!file->still_running) || (file->buffer_pos > want))
        return 0;

    /* attempt to fill buffer */
    do
    {
        FD_ZERO(&fdread);
        FD_ZERO(&fdwrite);
        FD_ZERO(&fdexcep);

        /* set a suitable timeout to fail on */
        timeout.tv_sec = 60; /* 1 minute */
        timeout.tv_usec = 0;

        /* get file descriptors from the transfers */
        curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

        rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);

        switch(rc) {
        case -1:
            /* select error */
            break;

        case 0:
            break;

        default:
            /* timeout or readable/writable sockets */
            /* note we *could* be more efficient and not wait for
             * CURLM_CALL_MULTI_PERFORM to clear here and check it on re-entry
             * but that gets messy */
            while(curl_multi_perform(multi_handle, &file->still_running) ==
                  CURLM_CALL_MULTI_PERFORM);

            break;
        }
    } while(file->still_running && (file->buffer_pos < want));
    return 1;
}