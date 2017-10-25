static long ftp_state_timeout(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  struct FTP *ftp = conn->proto.ftp;
  long timeout_ms=360000; /* in milliseconds */

  if(data->set.ftp_response_timeout )
    /* if CURLOPT_FTP_RESPONSE_TIMEOUT is set, use that to determine remaining
       time.  Also, use ftp->response because FTP_RESPONSE_TIMEOUT is supposed
       to govern the response for any given ftp response, not for the time
       from connect to the given ftp response. */
    timeout_ms = data->set.ftp_response_timeout*1000 - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), ftp->response); /* spent time */
  else if(data->set.timeout)
    /* if timeout is requested, find out how much remaining time we have */
    timeout_ms = data->set.timeout*1000 - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), conn->now); /* spent time */
  else
    /* Without a requested timeout, we only wait 'response_time' seconds for
       the full response to arrive before we bail out */
    timeout_ms = ftp->response_time*1000 -
      Curl_tvdiff(Curl_tvnow(), ftp->response); /* spent time */

  return timeout_ms;
}