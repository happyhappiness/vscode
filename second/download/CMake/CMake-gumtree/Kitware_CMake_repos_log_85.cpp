snprintf(service_name, service_length +
             strlen(conn->socks_proxy.host.name)+2, "%s/%s",
             service, conn->socks_proxy.host.name);