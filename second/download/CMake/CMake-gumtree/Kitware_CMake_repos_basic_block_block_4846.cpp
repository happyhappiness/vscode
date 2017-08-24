f((data->easy_conn->http_proxy.proxytype != CURLPROXY_HTTPS ||
           data->easy_conn->bits.proxy_ssl_connected[FIRSTSOCKET]) &&
           (data->easy_conn->tunnel_state[FIRSTSOCKET] != TUNNEL_CONNECT)) {
          rc = CURLM_CALL_MULTI_PERFORM;
          /* initiate protocol connect phase */
          multistate(data, CURLM_STATE_SENDPROTOCONNECT);
        }