static void close_secondarysocket(struct connectdata *conn)
{
  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET]) {
    Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
    conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
  }
  conn->bits.tcpconnect[SECONDARYSOCKET] = FALSE;
}