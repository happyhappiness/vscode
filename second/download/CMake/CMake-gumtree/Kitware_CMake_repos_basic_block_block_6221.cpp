{
    conn->bits.tcpconnect[FIRSTSOCKET] = FALSE;
    result = Curl_connecthost(conn, conn->dns_entry);
    if(result)
      return result;
  }