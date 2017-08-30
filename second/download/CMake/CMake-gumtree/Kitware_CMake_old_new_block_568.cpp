{
  OM_uint32 major_status, minor_status;
  gss_buffer_desc token = GSS_C_EMPTY_BUFFER;
  char name[2048];
  const char* service = "HTTP";

  token.length = strlen(service) + 1 + strlen(proxy ? conn->proxy.name :
                                              conn->host.name) + 1;
  if(token.length + 1 > sizeof(name))
    return EMSGSIZE;

  snprintf(name, sizeof(name), "%s@%s", service, proxy ? conn->proxy.name :
           conn->host.name);

  token.value = (void *) name;
  major_status = gss_import_name(&minor_status,
                                 &token,
                                 GSS_C_NT_HOSTBASED_SERVICE,
                                 server);

  return GSS_ERROR(major_status) ? -1 : 0;
}