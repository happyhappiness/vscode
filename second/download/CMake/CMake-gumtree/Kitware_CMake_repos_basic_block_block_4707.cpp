{
      /* remember the most recently used connection */
      data->state.lastconnect = conn;

      infof(data, "Connection #%ld to host %s left intact\n",
            conn->connection_id,
            conn->bits.socksproxy ? conn->socks_proxy.host.dispname :
            conn->bits.httpproxy ? conn->http_proxy.host.dispname :
            conn->bits.conn_to_host ? conn->conn_to_host.dispname :
            conn->host.dispname);
    }