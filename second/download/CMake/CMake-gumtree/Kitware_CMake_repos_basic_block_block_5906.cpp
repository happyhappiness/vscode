f(Curl_resolver_asynch()) {
          /* ip_addr_str[0] is NUL only if the resolving of the name hasn't
             completed yet and until then we don't re-use this connection */
          if(!check->ip_addr_str[0]) {
            infof(data,
                  "Connection #%ld is still name resolving, can't reuse\n",
                  check->connection_id);
            continue;
          }
        }