static OSStatus SocketRead(SSLConnectionRef connection,
                           void *data,          /* owned by
                                                 * caller, data
                                                 * RETURNED */
                           size_t *dataLength)  /* IN/OUT */
{
  size_t bytesToGo = *dataLength;
  size_t initLen = bytesToGo;
  UInt8 *currData = (UInt8 *)data;
  /*int sock = *(int *)connection;*/
  struct ssl_connect_data *connssl = (struct ssl_connect_data *)connection;
  int sock = BACKEND->ssl_sockfd;
  OSStatus rtn = noErr;
  size_t bytesRead;
  ssize_t rrtn;
  int theErr;

  *dataLength = 0;

  for(;;) {
    bytesRead = 0;
    rrtn = read(sock, currData, bytesToGo);
    if(rrtn <= 0) {
      /* this is guesswork... */
      theErr = errno;
      if(rrtn == 0) { /* EOF = server hung up */
        /* the framework will turn this into errSSLClosedNoNotify */
        rtn = errSSLClosedGraceful;
      }
      else /* do the switch */
        switch(theErr) {
          case ENOENT:
            /* connection closed */
            rtn = errSSLClosedGraceful;
            break;
          case ECONNRESET:
            rtn = errSSLClosedAbort;
            break;
          case EAGAIN:
            rtn = errSSLWouldBlock;
            BACKEND->ssl_direction = false;
            break;
          default:
            rtn = ioErr;
            break;
        }
      break;
    }
    else {
      bytesRead = rrtn;
    }
    bytesToGo -= bytesRead;
    currData  += bytesRead;

    if(bytesToGo == 0) {
      /* filled buffer with incoming data, done */
      break;
    }
  }
  *dataLength = initLen - bytesToGo;

  return rtn;
}