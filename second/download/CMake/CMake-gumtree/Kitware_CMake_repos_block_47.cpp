{
    /* this really shouldn't be repeated here, but can't help it */
    if(service == srv_host) {
      result = Curl_ftpsend(conn, "AUTH GSSAPI");
      if(result)
        return -2;

      if(Curl_GetFTPResponse(&nread, conn, NULL))
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
      maj = Curl_gss_init_sec_context(data,
                                      &min,
                                      context,
                                      gssname,
                                      &Curl_krb5_mech_oid,
                                      &chan,
                                      gssresp,
                                      &output_buffer,
                                      TRUE,
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
        char *cmd;

        result = Curl_base64_encode(data, (char *)output_buffer.value,
                                    output_buffer.length, &p, &base64_sz);
        if(result) {
          Curl_infof(data, "base64-encoding: %s\n",
                     curl_easy_strerror(result));
          ret = AUTH_ERROR;
          break;
        }

        cmd = aprintf("ADAT %s", p);
        if(cmd)
          result = Curl_ftpsend(conn, cmd);
        else
          result = CURLE_OUT_OF_MEMORY;

        free(p);

        if(result) {
          ret = -2;
          break;
        }

        if(Curl_GetFTPResponse(&nread, conn, NULL)) {
          ret = -1;
          break;
        }

        if(data->state.buffer[0] != '2' && data->state.buffer[0] != '3') {
          Curl_infof(data, "Server didn't accept auth data\n");
          ret = AUTH_ERROR;
          break;
        }

        p = data->state.buffer + 4;
        p = strstr(p, "ADAT=");
        if(p) {
          result = Curl_base64_decode(p + 5,
                                      (unsigned char **)&_gssresp.value,
                                      &_gssresp.length);
          if(result) {
            Curl_failf(data, "base64-decoding: %s",
                       curl_easy_strerror(result));
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