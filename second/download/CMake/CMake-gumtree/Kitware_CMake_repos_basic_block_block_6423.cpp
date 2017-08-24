{
    length = write(sock,
                   (char *)dataPtr + bytesSent,
                   dataLen - bytesSent);
  }