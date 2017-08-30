   * Connect to server/proxy

   *************************************************************/

  result= Curl_connecthost(conn,

                           conn->hostaddr,

                           conn->port,

                           &conn->firstsocket,

                           &addr);

  if(CURLE_OK == result) {

    /* All is cool, then we store the current information from the hostaddr

       struct to the serv_addr, as it might be needed later. The address

       returned from the function above is crucial here. */

#ifdef ENABLE_IPV6

    conn->serv_addr = addr;

#else

    memset((char *) &conn->serv_addr, '\0', sizeof(conn->serv_addr));

    memcpy((char *)&(conn->serv_addr.sin_addr),

           (struct in_addr *)addr, sizeof(struct in_addr));

    conn->serv_addr.sin_family = conn->hostaddr->h_addrtype;

    conn->serv_addr.sin_port = htons(conn->port);

#endif

  }



  return result;

}



static CURLcode CreateConnection(struct SessionHandle *data,

                                 struct connectdata **in_connect)

{

