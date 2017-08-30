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

      failf(data, "Server does not grok %s", *modep);

      continue;

    }

    else

      break;

  }

  

  if (!*modep) {

    sclose(portsock);

    return CURLE_FTP_PORT_FAILED;

  }

  /* we set the secondary socket variable to this for now, it

     is only so that the cleanup function will close it in case

     we fail before the true secondary stuff is made */

  conn->secondarysocket = portsock;

  

#else

  /******************************************************************

   *

   * Here's a piece of IPv4-specific code coming up

   *

   */

  struct sockaddr_in sa;

  struct Curl_dns_entry *h=NULL;

  unsigned short porttouse;

  char myhost[256] = "";

  bool sa_filled_in = FALSE;



  if(data->set.ftpport) {

    if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {

      h = Curl_resolv(data, myhost, 0);

    }

    else {

      size_t len = strlen(data->set.ftpport);

      if(len>1)

        h = Curl_resolv(data, data->set.ftpport, 0);

      if(h)

        strcpy(myhost, data->set.ftpport); /* buffer overflow risk */

    }

  }

  if(! *myhost) {

    /* pick a suitable default here */



#ifdef __hpux     

    int sslen;

#else 

    socklen_t sslen;

#endif

    

    sslen = sizeof(sa);

    if (getsockname(conn->firstsocket, (struct sockaddr *)&sa, &sslen) < 0) {

      failf(data, "getsockname() failed");

      return CURLE_FTP_PORT_FAILED;

    }



    sa_filled_in = TRUE; /* the sa struct is filled in */

  }



  if(h)

    /* when we return from here, we can forget about this */

    Curl_resolv_unlock(h);



  if ( h || sa_filled_in) {

    if( (portsock = (int)socket(AF_INET, SOCK_STREAM, 0)) >= 0 ) {

      int size;

      

      /* we set the secondary socket variable to this for now, it

         is only so that the cleanup function will close it in case

         we fail before the true secondary stuff is made */

      conn->secondarysocket = portsock;



      if(!sa_filled_in) {

        memset((char *)&sa, 0, sizeof(sa));

        memcpy((char *)&sa.sin_addr,

               h->addr->h_addr,

               h->addr->h_length);

        sa.sin_family = AF_INET;

        sa.sin_addr.s_addr = INADDR_ANY;

      }



      sa.sin_port = 0;

      size = sizeof(sa);

      

      if(bind(portsock, (struct sockaddr *)&sa, size) >= 0) {

        /* we succeeded to bind */

        struct sockaddr_in add;

#ifdef __hpux     

        int socksize = sizeof(add);

#else 

        socklen_t socksize = sizeof(add);

#endif



        if(getsockname(portsock, (struct sockaddr *) &add,

                       &socksize)<0) {

          failf(data, "getsockname() failed");

          return CURLE_FTP_PORT_FAILED;

        }

        porttouse = ntohs(add.sin_port);

        

        if ( listen(portsock, 1) < 0 ) {

          failf(data, "listen(2) failed on socket");

          return CURLE_FTP_PORT_FAILED;

