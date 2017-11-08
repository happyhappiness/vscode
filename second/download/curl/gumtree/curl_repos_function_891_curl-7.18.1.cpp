static long ftp_state_timeout(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  long timeout_ms=360000; /* in milliseconds */

  if(data->set.ftp_response_timeout )
    /* if CURLOPT_FTP_RESPONSE_TIMEOUT is set, use that to determine remaining
       time.  Also, use ftp->response because FTP_RESPONSE_TIMEOUT is supposed
       to govern the response for any given ftp response, not for the time
       from connect to the given ftp response. */
    timeout_ms = data->set.ftp_response_timeout - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), ftpc->response); /* spent time */
  else if(data->set.timeout)
    /* if timeout is requested, find out how much remaining time we have */
    timeout_ms = data->set.timeout - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), conn->now); /* spent time */
  else
    /* Without a requested timeout, we only wait 'response_time' seconds for
       the full response to arrive before we bail out */
    timeout_ms = ftpc->response_time -
      Curl_tvdiff(Curl_tvnow(), ftpc->response); /* spent time */

  return timeout_ms;
}