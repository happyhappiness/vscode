{
  RTMP *r = conn->proto.generic;
  SET_RCVTIMEO(tv, 10);

  r->m_sb.sb_socket = conn->sock[FIRSTSOCKET];

  /* We have to know if it's a write before we send the
   * connect request packet
   */
  if(conn->data->set.upload)
    r->Link.protocol |= RTMP_FEATURE_WRITE;

  /* For plain streams, use the buffer toggle trick to keep data flowing */
  if(!(r->Link.lFlags & RTMP_LF_LIVE) &&
     !(r->Link.protocol & RTMP_FEATURE_HTTP))
    r->Link.lFlags |= RTMP_LF_BUFX;

  (void)curlx_nonblock(r->m_sb.sb_socket, FALSE);
  setsockopt(r->m_sb.sb_socket, SOL_SOCKET, SO_RCVTIMEO,
             (char *)&tv, sizeof(tv));

  if(!RTMP_Connect1(r, NULL))
    return CURLE_FAILED_INIT;

  /* Clients must send a periodic BytesReceived report to the server */
  r->m_bSendCounter = true;

  *done = TRUE;
  conn->recv[FIRSTSOCKET] = rtmp_recv;
  conn->send[FIRSTSOCKET] = rtmp_send;
  return CURLE_OK;
}