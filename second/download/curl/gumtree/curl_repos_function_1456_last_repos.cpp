struct connectdata *
Curl_oldest_idle_connection(struct Curl_easy *data)
{
  struct conncache *bc = data->state.conn_cache;
  struct curl_hash_iterator iter;
  struct curl_llist_element *curr;
  struct curl_hash_element *he;
  time_t highscore =- 1;
  time_t score;
  struct curltime now;
  struct connectdata *conn_candidate = NULL;
  struct connectbundle *bundle;

  now = Curl_tvnow();

  Curl_hash_start_iterate(&bc->hash, &iter);

  he = Curl_hash_next_element(&iter);
  while(he) {
    struct connectdata *conn;

    bundle = he->ptr;

    curr = bundle->conn_list.head;
    while(curr) {
      conn = curr->ptr;

      if(!conn->inuse) {
        /* Set higher score for the age passed since the connection was used */
        score = Curl_tvdiff(now, conn->now);

        if(score > highscore) {
          highscore = score;
          conn_candidate = conn;
        }
      }
      curr = curr->next;
    }

    he = Curl_hash_next_element(&iter);
  }

  return conn_candidate;
}