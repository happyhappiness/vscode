{
      /* In all these states, the code will blindly access 'data->easy_conn'
         so this is precaution that it isn't NULL. And it silences static
         analyzers. */
      failf(data, "In state %d with no easy_conn, bail out!\n", data->mstate);
      return CURLM_INTERNAL_ERROR;
    }