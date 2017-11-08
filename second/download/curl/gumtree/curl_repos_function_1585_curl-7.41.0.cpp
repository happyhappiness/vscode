static ssize_t rtmp_recv(struct connectdata *conn, int sockindex, char *buf,
                         size_t len, CURLcode *err)
{
  RTMP *r = conn->proto.generic;
  ssize_t nread;

  (void)sockindex; /* unused */

  nread = RTMP_Read(r, buf, curlx_uztosi(len));
  if(nread < 0) {
    if(r->m_read.status == RTMP_READ_COMPLETE ||
        r->m_read.status == RTMP_READ_EOF) {
      conn->data->req.size = conn->data->req.bytecount;
      nread = 0;
    }
    else
      *err = CURLE_RECV_ERROR;
  }
  return nread;
}