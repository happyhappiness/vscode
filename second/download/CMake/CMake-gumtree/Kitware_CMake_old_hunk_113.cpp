

  /* We do some initial setup here, all those fields that can't be just 0 */



  data->state.headerbuff = malloc(HEADERSIZE);

  if(!data->state.headerbuff) {

    DEBUGF(fprintf(stderr, "Error: malloc of headerbuff failed\n"));

