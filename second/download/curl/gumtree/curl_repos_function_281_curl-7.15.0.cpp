static int
get_gss_name(struct connectdata *conn, gss_name_t *server)
{
  struct negotiatedata *neg_ctx = &conn->data->state.negotiate;
  OM_uint32 major_status, minor_status;
  gss_buffer_desc token = GSS_C_EMPTY_BUFFER;
  char name[2048];
  const char* service;

  /* GSSAPI implementation by Globus (known as GSI) requires the name to be
     of form "<service>/<fqdn>" instead of <service>@<fqdn> (ie. slash instead
     of at-sign). Also GSI servers are often identified as 'host' not 'khttp'.
     Change following lines if you want to use GSI */

  /* IIS uses the <service>@<fqdn> form but uses 'http' as the service name */

  if (neg_ctx->gss)
    service = "KHTTP";
  else
    service = "HTTP";

  token.length = strlen(service) + 1 + strlen(conn->host.name) + 1;
  if (token.length + 1 > sizeof(name))
    return EMSGSIZE;

  snprintf(name, sizeof(name), "%s@%s", service, conn->host.name);

  token.value = (void *) name;
  major_status = gss_import_name(&minor_status,
                                 &token,
                                 GSS_C_NT_HOSTBASED_SERVICE,
                                 server);

  return GSS_ERROR(major_status) ? -1 : 0;
}