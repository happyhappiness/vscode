{

  va_list ap;

  size_t len;

  char error[CURL_ERROR_SIZE + 2];

  va_start(ap, fmt);



  vsnprintf(error, CURL_ERROR_SIZE, fmt, ap);

  len = strlen(error);



  if(data->set.errorbuffer && !data->state.errorbuf) {

    strcpy(data->set.errorbuffer, error);

    data->state.errorbuf = TRUE; /* wrote error string */

  }

  if(data->set.verbose) {

    error[len] = '\n';

    error[++len] = '\0';

    Curl_debug(data, CURLINFO_TEXT, error, len, NULL);

  }



  va_end(ap);

