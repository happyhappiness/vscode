  if(data->set.errorbuffer && !data->state.errorbuf) {

    vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);

    data->state.errorbuf = TRUE; /* wrote error string */

  }

  va_end(ap);

}

