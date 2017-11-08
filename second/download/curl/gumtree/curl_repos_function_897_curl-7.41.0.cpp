int Curl_closesocket(struct connectdata *conn,
                      curl_socket_t sock)
{
  if(conn && conn->fclosesocket) {
    if((sock == conn->sock[SECONDARYSOCKET]) &&
       conn->sock_accepted[SECONDARYSOCKET])
      /* if this socket matches the second socket, and that was created with
         accept, then we MUST NOT call the callback but clear the accepted
         status */
      conn->sock_accepted[SECONDARYSOCKET] = FALSE;
    else
      return conn->fclosesocket(conn->closesocket_client, sock);
  }

  if(conn)
    /* tell the multi-socket code about this */
    Curl_multi_closed(conn, sock);

  sclose(sock);

  return 0;
}