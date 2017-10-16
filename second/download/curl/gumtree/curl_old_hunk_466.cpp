        return -1;

      if(data->state.buffer[0] != '3')
        return -1;
    }

    gssbuf.value = data->state.buffer;
    gssbuf.length = snprintf(gssbuf.value, BUFSIZE, "%s@%s", service, host);
    maj = gss_import_name(&min, &gssbuf, GSS_C_NT_HOSTBASED_SERVICE, &gssname);
    if(maj != GSS_S_COMPLETE) {
      gss_release_name(&min, &gssname);
      if(service == srv_host) {
        Curl_failf(data, "Error importing service name %s", gssbuf.value);
        return AUTH_ERROR;
      }
      service = srv_host;
      continue;
    }
    {
      gss_OID t;
      gss_display_name(&min, gssname, &gssbuf, &t);
      Curl_infof(data, "Trying against %s\n", gssbuf.value);
      gss_release_buffer(&min, &gssbuf);
    }
    gssresp = GSS_C_NO_BUFFER;
    *context = GSS_C_NO_CONTEXT;

    do {
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
                                 &gssbuf,
                                 NULL,
                                 NULL);

      if(gssresp) {
        free(_gssresp.value);
        gssresp = NULL;
