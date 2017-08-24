f(tn->subnegotiation[option] == CURL_YES) {
      /* send information to achieve this option*/
      tn->us[option] = CURL_YES;
      send_negotiation(conn, CURL_WILL, option);
      sendsuboption(conn, option);
    }