f(!Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL, sockindex))
      Curl_ssl_delsessionid(conn, old_ssl_sessionid)