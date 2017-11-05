ap_rvputs(r, ap_get_server_name(r), " (via ", r->connection->local_ip,
                  ")</h1>\n\n", NULL);