{
      msgbuf[sizeof(msgbuf)-1] = '\0';
      /* strip trailing '\r\n' or '\n' */
      p = strrchr(msgbuf, '\n');
      if(p && (p - msgbuf) >= 2)
        *p = '\0';
      p = strrchr(msgbuf, '\r');
      if(p && (p - msgbuf) >= 1)
        *p = '\0';
      msg = msgbuf;
    }