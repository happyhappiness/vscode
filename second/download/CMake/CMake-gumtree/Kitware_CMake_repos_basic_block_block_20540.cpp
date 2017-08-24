{
    uv_close((uv_handle_t*) pipe->pipe.conn.eof_timer, eof_timer_close_cb);
    pipe->pipe.conn.eof_timer = NULL;
  }