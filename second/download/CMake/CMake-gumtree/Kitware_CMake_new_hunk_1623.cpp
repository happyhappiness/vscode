 */

static void

ftp_pasv_verbose(struct connectdata *conn,

                 Curl_addrinfo *ai,

                 char *newhost, /* ascii version */

                 int port)

{

  char buf[256];

  Curl_printable_address(ai, buf, sizeof(buf));

  infof(conn->data, "Connecting to %s (%s) port %d\n", newhost, buf, port);

}



/***********************************************************************

