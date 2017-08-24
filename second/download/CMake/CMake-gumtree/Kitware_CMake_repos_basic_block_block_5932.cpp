f(conn->bits.tunnel_proxy && conn->bits.httpproxy &&
       (conn->tunnel_state[FIRSTSOCKET] != TUNNEL_COMPLETE))
      /* when using an HTTP tunnel proxy, await complete tunnel establishment
         before proceeding further. Return CURLE_OK so we'll be called again */
      return CURLE_OK;