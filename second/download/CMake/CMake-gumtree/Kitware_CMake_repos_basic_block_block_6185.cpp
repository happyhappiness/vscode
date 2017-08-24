f(conn_temp->bundle->num_connections < max_host_connections &&
         data->state.conn_cache->num_connections < max_total_connections) {
        /* We want a new connection anyway */
        reuse = FALSE;

        infof(data, "We can reuse, but we want a new connection anyway\n");
      }