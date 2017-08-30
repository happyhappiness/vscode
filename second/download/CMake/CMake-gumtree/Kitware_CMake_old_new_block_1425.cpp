{
    buf = aprintf(fmt, ap);
    ret = buffer_write(&conn->out_buffer, buf, strlen(buf));
    free(buf);
    return ret;
  }