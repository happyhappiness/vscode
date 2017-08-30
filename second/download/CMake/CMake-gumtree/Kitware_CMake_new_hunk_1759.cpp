    }

  }



  if(data->set.encoding) {

    if(conn->allocptr.accept_encoding)

      free(conn->allocptr.accept_encoding);

    conn->allocptr.accept_encoding =

      aprintf("Accept-Encoding: %s\015\012", data->set.encoding);

  }



  conn->bytecount = 0;

  conn->headerbytecount = 0;

  

  if(-1 == conn->firstsocket) {

    bool connected;



    /* Connect only if not already connected! */

    result = ConnectPlease(conn, hostaddr, &connected);



    if(connected)

      result = Curl_protocol_connect(conn, hostaddr);



    if(CURLE_OK != result)

      return result;

  }

  else {

    Curl_pgrsTime(data, TIMER_CONNECT); /* we're connected already */

    if(data->set.verbose)

      verboseconnect(conn, hostaddr);

  }



  conn->now = Curl_tvnow(); /* time this *after* the connect is done, we

                               set this here perhaps a second time */



#ifdef __EMX__

  /* 20000330 mgs

