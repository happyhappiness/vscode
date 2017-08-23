{
    snprintf(data->set.errorbuffer, CURL_ERROR_SIZE, "%s", data->state.buffer);
    data->state.errorbuf = TRUE; /* wrote error string */
  }