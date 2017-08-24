{
    /* this is a new one as head, expire it */
    Curl_pipeline_leave_write(conn); /* not in use yet */
    Curl_expire(conn->send_pipe.head->ptr, 0, EXPIRE_RUN_NOW);
  }