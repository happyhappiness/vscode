f(reuse && !force_reuse && IsPipeliningPossible(data, conn_temp)) {
    size_t pipelen = conn_temp->send_pipe.size + conn_temp->recv_pipe.size;
    if(pipelen > 0) {
      infof(data, "Found connection %ld, with requests in the pipe (%zu)\n",
            conn_temp->connection_id, pipelen);

      if(conn_temp->bundle->num_connections < max_host_connections &&
         data->state.conn_cache->num_connections < max_total_connections) {
        /* We want a new connection anyway */
        reuse = FALSE;

        infof(data, "We can reuse, but we want a new connection anyway\n");
      }
    }
  }