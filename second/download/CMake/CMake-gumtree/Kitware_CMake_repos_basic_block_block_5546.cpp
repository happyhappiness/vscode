{
    service.length = serviceptr_length;
    service.value = malloc(service.length);
    if(!service.value)
      return CURLE_OUT_OF_MEMORY;
    memcpy(service.value, serviceptr, service.length);

    gss_major_status = gss_import_name(&gss_minor_status, &service,
                                       (gss_OID) GSS_C_NULL_OID, &server);
  }