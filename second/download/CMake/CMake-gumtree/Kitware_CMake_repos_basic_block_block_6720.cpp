{
    /* BLOCKING call, this is bad but a work-around for now. Fixing this "the
       proper way" takes a whole lot of work. */
    CURLcode result = handshake(conn, num, FALSE, FALSE);
    if(result)
      /* handshake() writes error message on its own */
      *curlcode = result;
    else
      *curlcode = CURLE_AGAIN; /* then return as if this was a wouldblock */
    return -1;
  }