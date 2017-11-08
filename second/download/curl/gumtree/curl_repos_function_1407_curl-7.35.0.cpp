static int
get_gss_name(struct connectdata *conn, bool proxy,
             struct negotiatedata *neg_ctx)
{
  const char* service;
  size_t length;

  if(proxy && !conn->proxy.name)
    /* proxy auth requested but no given proxy name, error out! */
    return -1;

  /* GSSAPI implementation by Globus (known as GSI) requires the name to be
     of form "<service>/<fqdn>" instead of <service>@<fqdn> (ie. slash instead
     of at-sign). Also GSI servers are often identified as 'host' not 'khttp'.
     Change following lines if you want to use GSI */

  /* IIS uses the <service>@<fqdn> form but uses 'http' as the service name,
     and SSPI then generates an NTLM token. When using <service>/<fqdn> a
     Kerberos token is generated. */

  if(neg_ctx->gss)
    service = "KHTTP";
  else
    service = "HTTP";

  length = strlen(service) + 1 + strlen(proxy ? conn->proxy.name :
                                        conn->host.name) + 1;
  if(length + 1 > sizeof(neg_ctx->server_name))
    return EMSGSIZE;

  snprintf(neg_ctx->server_name, sizeof(neg_ctx->server_name), "%s/%s",
           service, proxy ? conn->proxy.name : conn->host.name);

  return 0;
}