     * The application kindly asks for a differently sized receive buffer.
     * If it seems reasonable, we'll use it.
     */
    data->set.buffer_size = va_arg(param, long);

    if(data->set.buffer_size > MAX_BUFSIZE)
      data->set.buffer_size = MAX_BUFSIZE; /* huge internal default */
    else if(data->set.buffer_size < 1)
      data->set.buffer_size = BUFSIZE;

    /* Resize only if larger than default buffer size. */
    if(data->set.buffer_size > BUFSIZE) {
      data->state.buffer = realloc(data->state.buffer,
                                   data->set.buffer_size + 1);
      if(!data->state.buffer) {
        DEBUGF(fprintf(stderr, "Error: realloc of buffer failed\n"));
        result = CURLE_OUT_OF_MEMORY;
      }
    }

    break;

