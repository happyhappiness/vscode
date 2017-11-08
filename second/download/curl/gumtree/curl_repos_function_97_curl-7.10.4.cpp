static CURLcode bindlocal(struct connectdata *conn,
                          int sockfd)
{
#if !defined(WIN32)||defined(__CYGWIN32__)
  /* We don't generally like checking for OS-versions, we should make this
     HAVE_XXXX based, although at the moment I don't have a decent test for
     this! */

#ifdef HAVE_INET_NTOA

#ifndef INADDR_NONE
#define INADDR_NONE (in_addr_t) ~0
#endif

  struct SessionHandle *data = conn->data;

  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if (strlen(data->set.device)<255) {
    struct sockaddr_in sa;
    struct Curl_dns_entry *h=NULL;
    size_t size;
    char myhost[256] = "";
    in_addr_t in;

    if(Curl_if2ip(data->set.device, myhost, sizeof(myhost))) {
      /*
       * We now have the numerical IPv4-style x.y.z.w in the 'myhost' buffer
       */
      h = Curl_resolv(data, myhost, 0);
    }
    else {
      if(strlen(data->set.device)>1) {
        /*
         * This was not an interface, resolve the name as a host name
         * or IP number
         */
        h = Curl_resolv(data, data->set.device, 0);
        if(h) {
          /* we know data->set.device is shorter than the myhost array */
          strcpy(myhost, data->set.device);
        }
      }
    }

    if(! *myhost) {
      /* need to fix this
         h=Curl_gethost(data,
         getmyhost(*myhost,sizeof(myhost)),
         hostent_buf,
         sizeof(hostent_buf));
      */
      return CURLE_HTTP_PORT_FAILED;
    }

    infof(data, "We bind local end to %s\n", myhost);

    in=inet_addr(myhost);
    if (INADDR_NONE != in) {

      if ( h ) {
        Curl_addrinfo *addr = h->addr;

        Curl_resolv_unlock(data, h);
        /* we don't need it anymore after this function has returned */

#ifdef ENABLE_IPV6
        (void)sa; /* prevent compiler warning */
        if( bind(sockfd, addr->ai_addr, addr->ai_addrlen) >= 0) {
          /* we succeeded to bind */
          struct sockaddr_in6 add;
	
          size = sizeof(add);
          if(getsockname(sockfd, (struct sockaddr *) &add,
                         (socklen_t *)&size)<0) {
            failf(data, "getsockname() failed");
            return CURLE_HTTP_PORT_FAILED;
          }
        }
#else
        memset((char *)&sa, 0, sizeof(sa));
        memcpy((char *)&sa.sin_addr, addr->h_addr, addr->h_length);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = in;
        sa.sin_port = 0; /* get any port */
	
        if( bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) >= 0) {
          /* we succeeded to bind */
          struct sockaddr_in add;
	
          size = sizeof(add);
          if(getsockname(sockfd, (struct sockaddr *) &add,
                         (socklen_t *)&size)<0) {
            failf(data, "getsockname() failed");
            return CURLE_HTTP_PORT_FAILED;
          }
        }
#endif
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
            failf(data, "errno %d", errno);
            break;
          } /* end of switch(errno) */
	
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

    return CURLE_OK;

  } /* end of device selection support */
#endif /* end of HAVE_INET_NTOA */
#endif /* end of not WIN32 */

  return CURLE_HTTP_PORT_FAILED;
}