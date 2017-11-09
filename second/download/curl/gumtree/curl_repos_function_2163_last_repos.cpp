time_t Curl_pp_state_timeout(struct pingpong *pp)
{
  struct connectdata *conn = pp->conn;
  struct Curl_easy *data = conn->data;
  time_t timeout_ms; /* in milliseconds */
  time_t timeout2_ms; /* in milliseconds */
  long response_time = (data->set.server_response_timeout)?
    data->set.server_response_timeout: pp->response_time;

  /* if CURLOPT_SERVER_RESPONSE_TIMEOUT is set, use that to determine
     remaining time, or use pp->response because SERVER_RESPONSE_TIMEOUT is
     supposed to govern the response for any given server response, not for
     the time from connect to the given server response. */

  /* Without a requested timeout, we only wait 'response_time' seconds for the
     full response to arrive before we bail out */
  timeout_ms = response_time -
    Curl_tvdiff(Curl_tvnow(), pp->response); /* spent time */

  if(data->set.timeout) {
    /* if timeout is requested, find out how much remaining time we have */
    timeout2_ms = data->set.timeout - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), conn->now); /* spent time */

    /* pick the lowest number */
    timeout_ms = CURLMIN(timeout_ms, timeout2_ms);
  }

  return timeout_ms;
}