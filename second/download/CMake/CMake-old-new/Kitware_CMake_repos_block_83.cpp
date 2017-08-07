{
    service_name = malloc(service_length +
                          strlen(conn->socks_proxy.host.name) + 2);
    if(!service_name)
      return CURLE_OUT_OF_MEMORY;
    snprintf(service_name, service_length +
             strlen(conn->socks_proxy.host.name)+2, "%s/%s",
             service, conn->socks_proxy.host.name);
  }