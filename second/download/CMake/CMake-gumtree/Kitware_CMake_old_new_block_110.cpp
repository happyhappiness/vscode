{
    service.value = malloc(strlen(serviceptr) +strlen(conn->proxy.name)+2);
    if(!service.value)
      return CURLE_OUT_OF_MEMORY;
    service.length = strlen(serviceptr) +strlen(conn->proxy.name)+1;
    snprintf(service.value, service.length+1, "%s@%s",
             serviceptr, conn->proxy.name);

    gss_major_status = gss_import_name(&gss_minor_status, &service,
                                       GSS_C_NT_HOSTBASED_SERVICE, &server);
  }