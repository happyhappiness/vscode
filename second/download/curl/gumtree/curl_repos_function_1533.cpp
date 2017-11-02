static CURLcode pausewrite(struct SessionHandle *data,
                           int type, /* what type of data */
                           const char *ptr,
                           size_t len)
{
  /* signalled to pause sending on this connection, but since we have data
     we want to send we need to dup it to save a copy for when the sending
     is again enabled */
  struct SingleRequest *k = &data->req;
  char *dupl = malloc(len);
  if(!dupl)
    return CURLE_OUT_OF_MEMORY;

  memcpy(dupl, ptr, len);

  /* store this information in the state struct for later use */
  data->state.tempwrite = dupl;
  data->state.tempwritesize = len;
  data->state.tempwritetype = type;

  /* mark the connection as RECV paused */
  k->keepon |= KEEP_RECV_PAUSE;

  DEBUGF(infof(data, "Pausing with %zu bytes in buffer for type %02x\n",
               len, type));

  return CURLE_OK;
}