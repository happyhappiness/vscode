{
          /* ... finally back to actually retry the DO phase */
          conn = *connp; /* re-assign conn since multi_reconnect_request
                            creates a new connection */
          result = conn->handler->do_it(conn, done);
        }