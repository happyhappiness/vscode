{
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    Curl_disconnect(*in_connect, FALSE); /* close the connection */
    *in_connect = NULL;           /* return a NULL */
  }