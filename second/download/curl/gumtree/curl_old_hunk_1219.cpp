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
