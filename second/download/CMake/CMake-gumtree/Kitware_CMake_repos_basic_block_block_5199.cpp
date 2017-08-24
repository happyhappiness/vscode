e(len > 0) {
    if(read_data(conn, fd, &conn->in_buffer))
      return -1;
    if(conn->in_buffer.size == 0) {
      if(bytes_read > 0)
        conn->in_buffer.eof_flag = 1;
      return bytes_read;
    }
    bytes_read = buffer_read(&conn->in_buffer, buffer, len);
    len -= bytes_read;
    total_read += bytes_read;
    buffer += bytes_read;
  }