          snprintf(tmp, sizeof(tmp), ",%u", ap[i]);

        else

          snprintf(tmp, sizeof(tmp), "%u", ap[i]);



        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=

            sizeof(portmsgbuf)) {

          continue;

        }

      }



      if (strcmp(*modep, "LPRT") == 0) {

        snprintf(tmp, sizeof(tmp), ",%d", plen);



        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >= sizeof(portmsgbuf))

          continue;

      }



      for (i = 0; i < plen; i++) {

        snprintf(tmp, sizeof(tmp), ",%u", pp[i]);



        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=

            sizeof(portmsgbuf)) {

          continue;

        }

      }



      result = Curl_ftpsendf(conn, "%s %s", *modep, portmsgbuf);

      if(result)

        return result;

    }



    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

    if(result)

      return result;



    if (ftpcode != 200) {

      continue;

    }

    else

      break;

  }



  if (!*modep) {

    sclose(portsock);

    failf(data, "PORT command attempts failed");

    return CURLE_FTP_PORT_FAILED;

  }

  /* we set the secondary socket variable to this for now, it

     is only so that the cleanup function will close it in case

     we fail before the true secondary stuff is made */

  conn->sock[SECONDARYSOCKET] = portsock;



#else

  /******************************************************************

   *

   * Here's a piece of IPv4-specific code coming up

   *

   */

  struct sockaddr_in sa;

  unsigned short porttouse;

  char myhost[256] = "";

  bool sa_filled_in = FALSE;

  Curl_addrinfo *addr = NULL;

  unsigned short ip[4];



  if(data->set.ftpport) {

    in_addr_t in;



    /* First check if the given name is an IP address */

    in=inet_addr(data->set.ftpport);



    if(in != CURL_INADDR_NONE)

      /* this is an IPv4 address */

      addr = Curl_ip2addr(in, data->set.ftpport, 0);

    else {

      if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {

        /* The interface to IP conversion provided a dotted address */

        in=inet_addr(myhost);

        addr = Curl_ip2addr(in, myhost, 0);

      }

      else if(strlen(data->set.ftpport)> 1) {

        /* might be a host name! */

        struct Curl_dns_entry *h=NULL;

        int rc = Curl_resolv(conn, myhost, 0, &h);

        if(rc == CURLRESOLV_PENDING)

          rc = Curl_wait_for_resolv(conn, &h);

        if(h) {

          addr = h->addr;

          /* when we return from this function, we can forget about this entry

             to we can unlock it now already */

          Curl_resolv_unlock(data, h);

        } /* (h) */

      } /* strlen */

    } /* CURL_INADDR_NONE */

  } /* data->set.ftpport */



  if(!addr) {

    /* pick a suitable default here */



    socklen_t sslen;



    sslen = sizeof(sa);

    if (getsockname(conn->sock[FIRSTSOCKET],

                    (struct sockaddr *)&sa, &sslen) < 0) {

      failf(data, "getsockname() failed");

      return CURLE_FTP_PORT_FAILED;

    }



    sa_filled_in = TRUE; /* the sa struct is filled in */

  }



  if (addr || sa_filled_in) {

    portsock = socket(AF_INET, SOCK_STREAM, 0);

    if(CURL_SOCKET_BAD != portsock) {

      socklen_t size;



      /* we set the secondary socket variable to this for now, it

         is only so that the cleanup function will close it in case

         we fail before the true secondary stuff is made */

      conn->sock[SECONDARYSOCKET] = portsock;



      if(!sa_filled_in) {

        memcpy(&sa, addr->ai_addr, sizeof(sa));

        sa.sin_addr.s_addr = INADDR_ANY;

      }



      sa.sin_port = 0;

      size = sizeof(sa);



      if(bind(portsock, (struct sockaddr *)&sa, size) >= 0) {

        /* we succeeded to bind */

        struct sockaddr_in add;

        socklen_t socksize = sizeof(add);



        if(getsockname(portsock, (struct sockaddr *) &add,

                       &socksize)<0) {

          failf(data, "getsockname() failed");

          return CURLE_FTP_PORT_FAILED;

        }

        porttouse = ntohs(add.sin_port);



        if ( listen(portsock, 1) < 0 ) {

          failf(data, "listen(2) failed on socket");

          return CURLE_FTP_PORT_FAILED;

