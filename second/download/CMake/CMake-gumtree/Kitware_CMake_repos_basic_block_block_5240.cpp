{
    free(conn->in_buffer.data);
    conn->in_buffer.data = NULL;
    conn->in_buffer.size = 0;
    conn->in_buffer.index = 0;
    /* FIXME: Is this really needed? */
    conn->in_buffer.eof_flag = 0;
  }