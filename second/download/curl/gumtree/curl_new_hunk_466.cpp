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
        Curl_failf(data, "Error importing service name %s", input_buffer.value);
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
