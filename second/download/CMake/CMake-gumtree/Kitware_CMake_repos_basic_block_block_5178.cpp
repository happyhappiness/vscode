{
  if(conn->bits.multiplex)
    /* when multiplexing, we can use it at once */
    return TRUE;

  if(!conn->writechannel_inuse && Curl_sendpipe_head(data, conn)) {
    /* Grab the channel */
    conn->writechannel_inuse = TRUE;
    return TRUE;
  }
  return FALSE;
}