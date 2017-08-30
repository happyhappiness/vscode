    }

  }



  if(-1 == conn->firstsocket) {

    /* Connect only if not already connected! */

    result = ConnectPlease(conn);

    if(CURLE_OK != result)

      return result;



    if(conn->curl_connect) {

      /* is there a connect() procedure? */



      /* set start time here for timeout purposes in the

       * connect procedure, it is later set again for the

       * progress meter purpose */

      conn->now = Curl_tvnow();



      /* Call the protocol-specific connect function */

      result = conn->curl_connect(conn);

      if(result != CURLE_OK)

        return result; /* pass back errors */

    }

  }



  Curl_pgrsTime(data, TIMER_CONNECT); /* we're connected */



  conn->now = Curl_tvnow(); /* time this *after* the connect is done */

  conn->bytecount = 0;

  conn->headerbytecount = 0;

  

  /* Figure out the ip-number and display the first host name it shows: */

#ifdef ENABLE_IPV6

  {

    char hbuf[NI_MAXHOST];

#ifdef NI_WITHSCOPEID

    const int niflags = NI_NUMERICHOST | NI_WITHSCOPEID;

#else

    const int niflags = NI_NUMERICHOST;

#endif

    struct addrinfo *ai = conn->serv_addr;



    if (getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0,

        niflags)) {

      snprintf(hbuf, sizeof(hbuf), "?");

    }

    if (ai->ai_canonname) {

      infof(data, "Connected to %s (%s) port %d\n", ai->ai_canonname, hbuf,

            conn->port);

    } else {

      infof(data, "Connected to %s port %d\n", hbuf, conn->port);

    }

  }

#else

  {

    struct in_addr in;

    (void) memcpy(&in.s_addr, &conn->serv_addr.sin_addr, sizeof (in.s_addr));

    infof(data, "Connected to %s (%s)\n", conn->hostaddr->h_name,

#if defined(HAVE_INET_NTOA_R)

          inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf))

#else

          inet_ntoa(in)

#endif

          );

  }

#endif



#ifdef __EMX__

  /* 20000330 mgs

