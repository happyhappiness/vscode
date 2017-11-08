void Curl_pipeline_leave_read(struct connectdata *conn)
{
  conn->readchannel_inuse = FALSE;
}