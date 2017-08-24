{
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