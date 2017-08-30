                            addr,

                            connectport,

                            &conn->secondarysocket,

                            &conninfo,

                            connected);



  Curl_resolv_unlock(addr); /* we're done using this address */



  /*

   * When this is used from the multi interface, this might've returned with

   * the 'connected' set to FALSE and thus we are now awaiting a non-blocking

   * connect to connect and we should not be "hanging" here waiting.

   */

  

  if((CURLE_OK == result) &&       

     data->set.verbose)

    /* this just dumps information about this second connection */

    ftp_pasv_verbose(conn, conninfo, newhostp, connectport);

  

  if(CURLE_OK != result)

    return result;



  if (data->set.tunnel_thru_httpproxy) {

    /* We want "seamless" FTP operations through HTTP proxy tunnel */

    result = Curl_ConnectHTTPProxyTunnel(conn, conn->secondarysocket,

                                         newhostp, newport);

    if(CURLE_OK != result)

      return result;

  }



  return CURLE_OK;

}



/*

 * Curl_ftp_nextconnect()

 *

 * This function shall be called when the second FTP connection has been

 * established and is confirmed connected.

 */



CURLcode Curl_ftp_nextconnect(struct connectdata *conn)

{

  struct SessionHandle *data=conn->data;

  char *buf = data->state.buffer; /* this is our buffer */

  CURLcode result;

  ssize_t nread;

  int ftpcode; /* for ftp status */



  /* the ftp struct is already inited in ftp_connect() */

  struct FTP *ftp = conn->proto.ftp;

  long *bytecountp = ftp->bytecountp;



  if(data->set.upload) {



