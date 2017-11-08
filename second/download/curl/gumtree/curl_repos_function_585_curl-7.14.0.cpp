int
Curl_sec_read(struct connectdata *conn, int fd, void *buffer, int length)
{
    size_t len;
    int rx = 0;

    if(conn->sec_complete == 0 || conn->data_prot == 0)
      return read(fd, buffer, length);

    if(conn->in_buffer.eof_flag){
      conn->in_buffer.eof_flag = 0;
      return 0;
    }

    len = buffer_read(&conn->in_buffer, buffer, length);
    length -= len;
    rx += len;
    buffer = (char*)buffer + len;

    while(length) {
      if(sec_get_data(conn, fd, &conn->in_buffer) < 0)
        return -1;
      if(conn->in_buffer.size == 0) {
        if(rx)
          conn->in_buffer.eof_flag = 1;
        return rx;
      }
      len = buffer_read(&conn->in_buffer, buffer, length);
      length -= len;
      rx += len;
      buffer = (char*)buffer + len;
    }
    return rx;
}