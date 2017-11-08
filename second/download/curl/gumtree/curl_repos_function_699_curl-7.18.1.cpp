static long
ConnectionKillOne(struct SessionHandle *data)
{
  long i;
  struct connectdata *conn;
  long highscore=-1;
  long connindex=-1;
  long score;
  struct timeval now;

  now = Curl_tvnow();

  for(i=0; data->state.connc && (i< data->state.connc->num); i++) {
    conn = data->state.connc->connects[i];

    if(!conn || conn->inuse)
      continue;

    /* Set higher score for the age passed since the connection was used */
    score = Curl_tvdiff(now, conn->now);

    if(score > highscore) {
      highscore = score;
      connindex = i;
    }
  }
  if(connindex >= 0) {
    /* Set the connection's owner correctly */
    conn = data->state.connc->connects[connindex];
    conn->data = data;

    /* the winner gets the honour of being disconnected */
    (void)Curl_disconnect(conn);

    /* clean the array entry */
    data->state.connc->connects[connindex] = NULL;
  }

  return connindex; /* return the available index or -1 */
}