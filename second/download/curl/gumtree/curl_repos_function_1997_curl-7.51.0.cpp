bool Curl_pipeline_checkget_read(struct Curl_easy *data,
                                 struct connectdata *conn)
{
  if(conn->bits.multiplex)
    /* when multiplexing, we can use it at once */
    return TRUE;

  if(!conn->readchannel_inuse && Curl_recvpipe_head(data, conn)) {
    /* Grab the channel */
    conn->readchannel_inuse = TRUE;
    return TRUE;
  }
  return FALSE;
}