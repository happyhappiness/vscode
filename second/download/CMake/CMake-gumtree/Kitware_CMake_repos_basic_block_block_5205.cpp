{
      static const char *enc = "ENC ";
      static const char *mic = "MIC ";
      if(prot_level == PROT_PRIVATE)
        socket_write(conn, fd, enc, 4);
      else
        socket_write(conn, fd, mic, 4);

      socket_write(conn, fd, cmd_buffer, cmd_size);
      socket_write(conn, fd, "\r\n", 2);
      infof(conn->data, "Send: %s%s\n", prot_level == PROT_PRIVATE?enc:mic,
            cmd_buffer);
      free(cmd_buffer);
    }