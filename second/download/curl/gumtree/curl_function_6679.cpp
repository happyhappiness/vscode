static int
krb5_auth(void *app_data, struct connectdata *conn)
{
  int ret = AUTH_OK;
  char *p;
  const char *host = conn->host.name;
  ssize_t nread;
  curl_socklen_t l = sizeof(conn->local_addr);
  struct SessionHandle *data = conn->data;
  CURLcode result;
  const char *service = "ftp", *srv_host = "host";
  gss_buffer_desc input_buffer, output_buffer, _gssresp, *gssresp;
  OM_uint32 maj, min;
  gss_name_t gssname;
  gss_ctx_id_t *context = app_data;
  struct gss_channel_bindings_struct chan;

  if(getsockname(conn->sock[FIRSTSOCKET],
                 (struct sockaddr *)LOCAL_ADDR, &l) < 0)
    perror("getsockname()");

  chan.initiator_addrtype = GSS_C_AF_INET;
  chan.initiator_address.length = l - 4;
  chan.initiator_address.value =
    &((struct sockaddr_in *)LOCAL_ADDR)->sin_addr.s_addr;
  chan.acceptor_addrtype = GSS_C_AF_INET;
  chan.acceptor_address.length = l - 4;
  chan.acceptor_address.value =
    &((struct sockaddr_in *)REMOTE_ADDR)->sin_addr.s_addr;
  chan.application_data.length = 0;
  chan.application_data.value = NULL;

  /* this loop will execute twice (once for service, once for host) */
  while(1) {
    /* this really shouldn't be repeated here, but can't help it */
    if(service == srv_host) {
      result = Curl_ftpsendf(conn, "AUTH GSSAPI");

      if(result)
        return -2;
      if(Curl_GetFTPResponse(&nread, conn, NULL))
        return -1;

      if(data->state.buffer[0] != '3')
        return -1;
    }

    input_buffer.value = data->state.buffer;
    input_buffer.length = snprintf(input_buffer.value, BUFSIZE, "%s@%s",
                                   service, host);
    maj = gss_import_name(&min, &input_buffer, GSS_C_NT_HOSTBASED_SERVICE,
                          &gssname);
    if(maj != GSS_S_COMPLETE) {
      gss_release_name(&min, &gssname);
      if(service == srv_host) {
        Curl_failf(data, "Error importing service name %s",
                   input_buffer.value);
        return AUTH_ERROR;
      }
      service = srv_host;
      continue;
    }
    /* We pass NULL as |output_name_type| to avoid a leak. */
    gss_display_name(&min, gssname, &output_buffer, NULL);
    Curl_infof(data, "Trying against %s\n", output_buffer.value);
    gssresp = GSS_C_NO_BUFFER;
    *context = GSS_C_NO_CONTEXT;

    do {
      /* Release the buffer at each iteration to avoid leaking: the first time
         we are releasing the memory from gss_display_name. The last item is
         taken care by a final gss_release_buffer. */
      gss_release_buffer(&min, &output_buffer);
      ret = AUTH_OK;
      maj = gss_init_sec_context(&min,
                                 GSS_C_NO_CREDENTIAL,
                                 context,
                                 gssname,
                                 GSS_C_NO_OID,
                                 GSS_C_MUTUAL_FLAG | GSS_C_REPLAY_FLAG,
                                 0,
                                 &chan,
                                 gssresp,
                                 NULL,
                                 &output_buffer,
                                 NULL,
                                 NULL);

      if(gssresp) {
        free(_gssresp.value);
        gssresp = NULL;
      }

      if(GSS_ERROR(maj)) {
        Curl_infof(data, "Error creating security context\n");
        ret = AUTH_ERROR;
        break;
      }

      if(output_buffer.length != 0) {
        if(Curl_base64_encode(data, (char *)output_buffer.value,
                              output_buffer.length, &p) < 1) {
          Curl_infof(data, "Out of memory base64-encoding\n");
          ret = AUTH_CONTINUE;
          break;
        }

        result = Curl_ftpsendf(conn, "ADAT %s", p);

        free(p);

        if(result) {
          ret = -2;
          break;
        }

        if(Curl_GetFTPResponse(&nread, conn, NULL)) {
          ret = -1;
          break;
        }

        if(data->state.buffer[0] != '2' && data->state.buffer[0] != '3'){
          Curl_infof(data, "Server didn't accept auth data\n");
          ret = AUTH_ERROR;
          break;
        }

        p = data->state.buffer + 4;
        p = strstr(p, "ADAT=");
        if(p) {
          _gssresp.length = Curl_base64_decode(p + 5, (unsigned char **)
                                               &_gssresp.value);
          if(_gssresp.length < 1) {
            Curl_failf(data, "Out of memory base64-encoding\n");
            ret = AUTH_CONTINUE;
            break;
          }
        }

        gssresp = &_gssresp;
      }
    } while(maj == GSS_S_CONTINUE_NEEDED);

    gss_release_name(&min, &gssname);
    gss_release_buffer(&min, &output_buffer);

    if(gssresp)
      free(_gssresp.value);

    if(ret == AUTH_OK || service == srv_host)
      return ret;

    service = srv_host;
  }
  return ret;
}