f(host_portno) {
    char *endp = NULL;
    *host_portno = '\0'; /* cut off number from host name */
    host_portno++;
    if(*host_portno) {
      long portparse = strtol(host_portno, &endp, 10);
      if((endp && *endp) || (portparse < 0) || (portparse > 65535)) {
        infof(data, "No valid port number in connect to host string (%s)\n",
              host_portno);
        hostptr = NULL;
        port = -1;
      }
      else
        port = (int)portparse; /* we know it will fit */
    }
  }