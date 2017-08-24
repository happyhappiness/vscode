{
    CURLMcode result;
    SIGPIPE_VARIABLE(pipe_st);

    sigpipe_ignore(data, &pipe_st);
    result = multi_runsingle(multi, now, data);
    sigpipe_restore(&pipe_st);

    if(result)
      returncode = result;

    data = data->next; /* operate on next handle */
  }