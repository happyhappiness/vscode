static CURLcode rtmp_disconnect(struct connectdata *conn,
                                bool dead_connection)
{
  RTMP *r = conn->proto.generic;
  (void)dead_connection;
  if(r) {
    conn->proto.generic = NULL;
    RTMP_Close(r);
    RTMP_Free(r);
  }
  return CURLE_OK;
}