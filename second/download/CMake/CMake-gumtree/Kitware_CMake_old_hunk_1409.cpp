    vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
    data->state.errorbuf = TRUE; /* wrote error string */

    if(data->set.verbose)
      Curl_debug(data, CURLINFO_TEXT, data->set.errorbuffer,
                 strlen(data->set.errorbuffer));
  }
  va_end(ap);
}
