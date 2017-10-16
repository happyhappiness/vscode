    env = curlx_getenv("CURL_CA_BUNDLE");
    if(env) {
      config->cacert = strdup(env);
      if(!config->cacert) {
        curl_free(env);
        helpf(global->errors, "out of memory\n");
        res = CURLE_OUT_OF_MEMORY;
        goto quit_curl;
      }
    }
    else {
      env = curlx_getenv("SSL_CERT_DIR");
      if(env) {
        config->capath = strdup(env);
        if(!config->capath) {
          curl_free(env);
          helpf(global->errors, "out of memory\n");
          res = CURLE_OUT_OF_MEMORY;
          goto quit_curl;
        }
      }
      else {
        env = curlx_getenv("SSL_CERT_FILE");
        if(env) {
          config->cacert = strdup(env);
          if(!config->cacert) {
            curl_free(env);
            helpf(global->errors, "out of memory\n");
            res = CURLE_OUT_OF_MEMORY;
            goto quit_curl;
          }
        }
      }
    }

    if(env)
      curl_free(env);
#ifdef WIN32
    else {
      res = FindWin32CACert(config, "curl-ca-bundle.crt");
      if(res)
        goto quit_curl;
    }
#endif
  }

  if(config->postfields) {
    if(config->use_httpget) {
      /* Use the postfields data for a http get */
      httpgetfields = strdup(config->postfields);
      Curl_safefree(config->postfields);
      if(!httpgetfields) {
        helpf(global->errors, "out of memory\n");
        res = CURLE_OUT_OF_MEMORY;
        goto quit_curl;
      }
      if(SetHTTPrequest(config,
                        (config->no_body?HTTPREQ_HEAD:HTTPREQ_GET),
                        &config->httpreq)) {
        res = CURLE_FAILED_INIT;
        goto quit_curl;
      }
    }
    else {
      if(SetHTTPrequest(config, HTTPREQ_SIMPLEPOST, &config->httpreq)) {
        res = CURLE_FAILED_INIT;
        goto quit_curl;
      }
    }
  }

  /* Single header file for all URLs */
  if(config->headerfile) {
    /* open file for output: */
    if(!curlx_strequal(config->headerfile, "-")) {
      FILE *newfile = fopen(config->headerfile, "wb");
      if(!newfile) {
        warnf(config, "Failed to open %s\n", config->headerfile);
        res = CURLE_WRITE_ERROR;
        goto quit_curl;
      }
      else {
        heads.filename = config->headerfile;
        heads.s_isreg = TRUE;
        heads.fopened = TRUE;
