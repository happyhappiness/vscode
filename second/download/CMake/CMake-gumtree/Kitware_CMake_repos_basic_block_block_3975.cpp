{
  SIGPIPE_VARIABLE(pipe_st);

  if(!data)
    return;

  sigpipe_ignore(data, &pipe_st);
  Curl_close(data);
  sigpipe_restore(&pipe_st);
}