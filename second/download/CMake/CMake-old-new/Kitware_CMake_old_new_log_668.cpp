snprintf(name, sizeof(name), "%s@%s", service, proxy ? conn->proxy.name :
           conn->host.name)