        return -1;

      if(data->state.buffer[0] != '3')
        return -1;
    }

    stringp = aprintf("%s@%s", service, host);
    if(!stringp)
      return -2;

    input_buffer.value = stringp;
    input_buffer.length = strlen(stringp);
    maj = gss_import_name(&min, &input_buffer, GSS_C_NT_HOSTBASED_SERVICE,
                          &gssname);
    free(stringp);
    if(maj != GSS_S_COMPLETE) {
      gss_release_name(&min, &gssname);
      if(service == srv_host) {
        Curl_failf(data, "Error importing service name %s@%s", service, host);
        return AUTH_ERROR;
      }
      service = srv_host;
      continue;
    }
    /* We pass NULL as |output_name_type| to avoid a leak. */
