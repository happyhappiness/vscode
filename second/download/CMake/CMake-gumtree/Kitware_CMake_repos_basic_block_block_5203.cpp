f(conn->in_buffer.eof_flag) {
    conn->in_buffer.eof_flag = 0;
    return 0;
  }