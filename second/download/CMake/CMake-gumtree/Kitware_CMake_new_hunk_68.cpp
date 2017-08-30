

  /* We do some initial setup here, all those fields that can't be just 0 */



  data->state.buffer = malloc(READBUFFER_SIZE + 1);

  if(!data->state.buffer) {

    DEBUGF(fprintf(stderr, "Error: malloc of buffer failed\n"));

    result = CURLE_OUT_OF_MEMORY;

