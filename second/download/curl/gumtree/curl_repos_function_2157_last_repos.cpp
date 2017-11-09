void Curl_pipeline_leave_write(struct connectdata *conn)
{
  conn->writechannel_inuse = FALSE;
}