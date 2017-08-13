
  /* prepare service name */
  if(strchr(serviceptr, '/')) {
    service.length = serviceptr_length;
    service.value = malloc(service.length);
    if(!service.value)
      return CURLE_OUT_OF_MEMORY;
    memcpy(service.value, serviceptr, service.length);

    gss_major_status = gss_import_name(&gss_minor_status, &service,
                                       (gss_OID) GSS_C_NULL_OID, &server);
  }
  else {
    service.value = malloc(serviceptr_length +
                           strlen(conn->socks_proxy.host.name)+2);
    if(!service.value)
      return CURLE_OUT_OF_MEMORY;
    service.length = serviceptr_length + strlen(conn->socks_proxy.host.name)+1;
    snprintf(service.value, service.length+1, "%s@%s",
             serviceptr, conn->socks_proxy.host.name);

    gss_major_status = gss_import_name(&gss_minor_status, &service,
                                       GSS_C_NT_HOSTBASED_SERVICE, &server);
