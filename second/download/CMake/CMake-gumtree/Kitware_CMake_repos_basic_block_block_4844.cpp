f((data->easy_conn->http_proxy.proxytype == CURLPROXY_HTTPS &&
            !data->easy_conn->bits.proxy_ssl_connected[FIRSTSOCKET]) ||
            (data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)) {
          multistate(data, CURLM_STATE_WAITPROXYCONNECT);
          break;
        }