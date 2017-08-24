{
        m->next = ev->list;
        m->socket.fd = s;
        m->socket.events = socketcb2poll(what);
        m->socket.revents = 0;
        ev->list = m;
        infof(easy, "socket cb: socket %d ADDED as %s%s\n", s,
              what&CURL_POLL_IN?"IN":"",
              what&CURL_POLL_OUT?"OUT":"");
      }