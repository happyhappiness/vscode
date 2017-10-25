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

  for(i=0; i< data->state.numconnects; i++) {
    conn = data->state.connects[i];

    if(!conn)
      continue;

    /*
     * By using the set policy, we score each connection.
     */
    switch(data->set.closepolicy) {
    case CURLCLOSEPOLICY_LEAST_RECENTLY_USED:
    default:
      /*
       * Set higher score for the age passed since the connection
       * was used.
       */
      score = Curl_tvdiff(now, conn->now);
      break;
    case CURLCLOSEPOLICY_OLDEST:
      /*
       * Set higher score for the age passed since the connection
       * was created.
       */
      score = Curl_tvdiff(now, conn->created);
      break;
    }

    if(score > highscore) {
      highscore = score;
      connindex = i;
    }
  }
  if(connindex >= 0) {

    /* the winner gets the honour of being disconnected */
    (void) Curl_disconnect(data->state.connects[connindex]);

    /* clean the array entry */
    data->state.connects[connindex] = NULL;
  }

  return connindex; /* return the available index or -1 */
}