static ssize_t rtmp_send(struct connectdata *conn, int sockindex,
                         const void *buf, size_t len, CURLcode *err)
{
  RTMP *r = conn->proto.generic;
  ssize_t num;

  (void)sockindex; /* unused */

  num = RTMP_Write(r, (char *)buf, curlx_uztosi(len));
  if(num < 0)
    *err = CURLE_SEND_ERROR;

  return num;
}