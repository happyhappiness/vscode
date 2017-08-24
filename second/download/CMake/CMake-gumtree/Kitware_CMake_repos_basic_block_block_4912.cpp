f(data) {
      SIGPIPE_VARIABLE(pipe_st);

      sigpipe_ignore(data, &pipe_st);
      result = multi_runsingle(multi, now, data);
      sigpipe_restore(&pipe_st);

      if(CURLM_OK >= result)
        /* get the socket(s) and check if the state has been changed since
           last */
        singlesocket(multi, data);
    }