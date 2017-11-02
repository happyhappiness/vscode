static CURLcode rtsp_done(struct connectdata *conn,
                          CURLcode status, bool premature)
{
  struct SessionHandle *data = conn->data;
  struct RTSP *rtsp = data->req.protop;
  CURLcode httpStatus;
  long CSeq_sent;
  long CSeq_recv;

  /* Bypass HTTP empty-reply checks on receive */
  if(data->set.rtspreq == RTSPREQ_RECEIVE)
    premature = TRUE;

  httpStatus = Curl_http_done(conn, status, premature);

  if(rtsp) {
    /* Check the sequence numbers */
    CSeq_sent = rtsp->CSeq_sent;
    CSeq_recv = rtsp->CSeq_recv;
    if((data->set.rtspreq != RTSPREQ_RECEIVE) && (CSeq_sent != CSeq_recv)) {
      failf(data,
            "The CSeq of this request %ld did not match the response %ld",
            CSeq_sent, CSeq_recv);
      return CURLE_RTSP_CSEQ_ERROR;
    }
    else if(data->set.rtspreq == RTSPREQ_RECEIVE &&
            (conn->proto.rtspc.rtp_channel == -1)) {
      infof(data, "Got an RTP Receive with a CSeq of %ld\n", CSeq_recv);
      /* TODO CPC: Server -> Client logic here */
    }
  }

  return httpStatus;
}