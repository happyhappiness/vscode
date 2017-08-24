{
    cp->ErrorMessage[length - 1] = 0;
    --length;
    if (length > 0 && cp->ErrorMessage[length - 1] == '\r') {
      cp->ErrorMessage[length - 1] = 0;
      --length;
    }
  }