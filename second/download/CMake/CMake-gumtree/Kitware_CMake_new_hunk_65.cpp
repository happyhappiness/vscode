     * The application kindly asks for a differently sized receive buffer.
     * If it seems reasonable, we'll use it.
     */
    arg = va_arg(param, long);

    if(arg > READBUFFER_MAX)
      arg = READBUFFER_MAX;
    else if(arg < 1)
      arg = READBUFFER_SIZE;
    else if(arg < READBUFFER_MIN)
      arg = READBUFFER_MIN;

    /* Resize if new size */
    if(arg != data->set.buffer_size) {
      char *newbuff = realloc(data->state.buffer, arg + 1);
      if(!newbuff) {
        DEBUGF(fprintf(stderr, "Error: realloc of buffer failed\n"));
        result = CURLE_OUT_OF_MEMORY;
      }
      else
        data->state.buffer = newbuff;
    }
    data->set.buffer_size = arg;

    break;

