{
      /* Successful read */
      ssize_t buflen = buf.len;

      if (is_ipc) {
        err = uv__stream_recv_cmsg(stream, &msg);
        if (err != 0) {
          stream->read_cb(stream, err, &buf);
          return;
        }
      }

#if defined(__MVS__)
      if (is_ipc && msg.msg_controllen > 0) {
        uv_buf_t blankbuf;
        int nread;
        struct iovec *old;

        blankbuf.base = 0;
        blankbuf.len = 0;
        old = msg.msg_iov;
        msg.msg_iov = (struct iovec*) &blankbuf;
        nread = 0;
        do {
          nread = uv__recvmsg(uv__stream_fd(stream), &msg, 0);
          err = uv__stream_recv_cmsg(stream, &msg);
          if (err != 0) {
            stream->read_cb(stream, err, &buf);
            msg.msg_iov = old;
            return;
          }
        } while (nread == 0 && msg.msg_controllen > 0);
        msg.msg_iov = old;
      }
#endif
      stream->read_cb(stream, nread, &buf);

      /* Return if we didn't fill the buffer, there is no more data to read. */
      if (nread < buflen) {
        stream->flags |= UV_STREAM_READ_PARTIAL;
        return;
      }
    }