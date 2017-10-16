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
