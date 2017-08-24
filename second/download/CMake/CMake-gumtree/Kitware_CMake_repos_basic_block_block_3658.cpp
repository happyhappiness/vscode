{
      free(conn->async.hostname);
      conn->async.hostname = NULL;
      return NULL;
    }