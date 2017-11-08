static CURLcode ConnectPlease(struct SessionHandle *data,
                              struct connectdata *conn)
{
#if defined(WIN32)
  unsigned long nonblock = 0;
  fd_set connectfd;
  struct timeval conntimeout;
#endif

#ifndef ENABLE_IPV6
  conn->firstsocket = socket(AF_INET, SOCK_STREAM, 0);

  memset((char *) &conn->serv_addr, '\0', sizeof(conn->serv_addr));
  memcpy((char *)&(conn->serv_addr.sin_addr),
         conn->hp->h_addr, conn->hp->h_length);
  conn->serv_addr.sin_family = conn->hp->h_addrtype;
  conn->serv_addr.sin_port = htons(conn->port);
#else
  /* IPv6-style */
  struct addrinfo *ai;
#endif

#if !defined(WIN32)||defined(__CYGWIN32__)
  /* We don't generally like checking for OS-versions, we should make this
     HAVE_XXXX based, although at the moment I don't have a decent test for
     this! */

#ifdef HAVE_INET_NTOA

#ifndef INADDR_NONE
#define INADDR_NONE (unsigned long) ~0
#endif

#ifndef ENABLE_IPV6
  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if (data->set.device && (strlen(data->set.device)<255)) {
    struct sockaddr_in sa;
    struct hostent *h=NULL;
    char *hostdataptr=NULL;
    size_t size;
    char myhost[256] = "";
    unsigned long in;

    if(Curl_if2ip(data->set.device, myhost, sizeof(myhost))) {
      h = Curl_gethost(data, myhost, &hostdataptr);
    }
    else {
      if(strlen(data->set.device)>1) {
        h = Curl_gethost(data, data->set.device, &hostdataptr);
      }
      if(h) {
        /* we know data->set.device is shorter than the myhost array */
        strcpy(myhost, data->set.device);
      }
    }

    if(! *myhost) {
      /* need to fix this
         h=Curl_gethost(data,
         getmyhost(*myhost,sizeof(myhost)),
         hostent_buf,
         sizeof(hostent_buf));
      */
      printf("in here\n");
    }

    infof(data, "We connect from %s\n", myhost);

    if ( (in=inet_addr(myhost)) != INADDR_NONE ) {

      if ( h ) {
        memset((char *)&sa, 0, sizeof(sa));
        memcpy((char *)&sa.sin_addr,
               h->h_addr,
               h->h_length);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = in;
        sa.sin_port = 0; /* get any port */
	
        if( bind(conn->firstsocket, (struct sockaddr *)&sa, sizeof(sa)) >= 0) {
          /* we succeeded to bind */
          struct sockaddr_in add;
	
          size = sizeof(add);
          if(getsockname(conn->firstsocket, (struct sockaddr *) &add,
                         (socklen_t *)&size)<0) {
            failf(data, "getsockname() failed");
            return CURLE_HTTP_PORT_FAILED;
          }
        }
        else {
          switch(errno) {
          case EBADF:
            failf(data, "Invalid descriptor: %d", errno);
            break;
          case EINVAL:
            failf(data, "Invalid request: %d", errno);
            break;
          case EACCES:
            failf(data, "Address is protected, user not superuser: %d", errno);
            break;
          case ENOTSOCK:
            failf(data,
                  "Argument is a descriptor for a file, not a socket: %d",
                  errno);
            break;
          case EFAULT:
            failf(data, "Inaccessable memory error: %d", errno);
            break;
          case ENAMETOOLONG:
            failf(data, "Address too long: %d", errno);
            break;
          case ENOMEM:
            failf(data, "Insufficient kernel memory was available: %d", errno);
            break;
          default:
            failf(data,"errno %d\n");
          } /* end of switch */
	
          return CURLE_HTTP_PORT_FAILED;
        } /* end of else */
	
      } /* end of if  h */
      else {
	failf(data,"could't find my own IP address (%s)", myhost);
	return CURLE_HTTP_PORT_FAILED;
      }
    } /* end of inet_addr */

    else {
      failf(data, "could't find my own IP address (%s)", myhost);
      return CURLE_HTTP_PORT_FAILED;
    }

    if(hostdataptr)
      free(hostdataptr); /* allocated by Curl_gethost() */

  } /* end of device selection support */
#endif  /* end of HAVE_INET_NTOA */
#endif /* end of not WIN32 */
#endif /*ENABLE_IPV6*/

  /*************************************************************
   * Connect to server/proxy
   *************************************************************/
#ifdef ENABLE_IPV6
  conn->firstsocket = -1;
  for (ai = conn->hp; ai; ai = ai->ai_next) {
    conn->firstsocket = socket(ai->ai_family,
                               ai->ai_socktype,
                               ai->ai_protocol);
    if (conn->firstsocket < 0)
      continue;

    if (connect(conn->firstsocket, ai->ai_addr, ai->ai_addrlen) < 0) {
      sclose(conn->firstsocket);
      conn->firstsocket = -1;
      continue;
    }

    break;
  }
  conn->ai = ai;
  if (conn->firstsocket < 0) {
    failf(data, strerror(errno));
    return CURLE_COULDNT_CONNECT;
  }
#else
  /* non-zero nonblock value sets socket as nonblocking under Win32 */
#if defined(WIN32)
  FD_ZERO (&connectfd);
  FD_SET(conn->firstsocket, &connectfd);
  if (conn->data->set.connecttimeout > 0) {
    nonblock = 1;
  }
  ioctlsocket(conn->firstsocket, FIONBIO, &nonblock);
#endif
  if (connect(conn->firstsocket,
              (struct sockaddr *) &(conn->serv_addr),
              sizeof(conn->serv_addr)
              ) < 0) {
#if defined(WIN32)
    conntimeout.tv_sec = conn->data->set.connecttimeout;
    conntimeout.tv_usec = 0;	
    if(-1 != select (conn->firstsocket + 1, NULL, &connectfd, NULL, &conntimeout)) {
      if (FD_ISSET(conn->firstsocket, &connectfd)) {
        /* shut off non-blocking again */
        nonblock = 0;
        ioctlsocket(conn->firstsocket, FIONBIO, &nonblock);
        return CURLE_OK;
      }
      else
        errno = EINTR;
    }
#endif
    switch(errno) {
#ifdef ECONNREFUSED
      /* this should be made nicer */
    case ECONNREFUSED:
      failf(data, "Connection refused");
      break;
    case EFAULT:
      failf(data, "Invalid socket address: %d",errno);
      break;
    case EISCONN:
      failf(data, "Socket already connected: %d",errno);
      break;
    case ETIMEDOUT:
      failf(data, "Timeout while accepting connection, server busy: %d",errno);
      break;
    case ENETUNREACH:
      failf(data, "Network is unreachable: %d",errno);
      break;
    case EADDRINUSE:
      failf(data, "Local address already in use: %d",errno);
      break;
    case EINPROGRESS:
      failf(data, "Socket is nonblocking and connection can not be completed immediately: %d",errno);
      break;
    case EALREADY:
      failf(data, "Socket is nonblocking and a previous connection attempt not completed: %d",errno);
      break;
    case EAGAIN:
      failf(data, "No more free local ports: %d",errno);
      break;
    case EACCES:
    case EPERM:
      failf(data, "Attempt to connect to broadcast address without socket broadcast flag or local firewall rule violated: %d",errno);
      break;
#endif
    case EINTR:
      failf(data, "Connection timed out");
      break;
    default:
      failf(data, "Can't connect to server: %d", errno);
      break;
    }
    return CURLE_COULDNT_CONNECT;
  }
#endif

  return CURLE_OK;
}