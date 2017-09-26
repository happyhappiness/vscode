    would_block = 0;
#endif

    request_count = 0;

    ClearScreen (getscreenhandle());
    printf("%s \n", ap_get_server_description());

    for (i=0;i<SERVER_NUM_STATUS;i++) {
        status_array[i] = 0;
    }

    for (i = 0; i < ap_threads_limit; ++i) {
