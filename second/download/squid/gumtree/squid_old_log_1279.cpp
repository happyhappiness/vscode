mb.Printf("EPRT |%d|%s|%d|%s",
              ( data.conn->local.isIPv6() ? 2 : 1 ),
              data.conn->local.toStr(buf,MAX_IPSTRLEN),
              comm_local_port(data.conn->fd), Ftp::crlf );