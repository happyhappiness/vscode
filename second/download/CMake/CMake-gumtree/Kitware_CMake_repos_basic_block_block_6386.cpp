{
    /* Decode the base-64 encoded challenge message */
    if(*chlg64 != '=') {
      result = Curl_base64_decode(chlg64, &chlg, &chlglen);
      if(result)
        return result;
    }

    /* Ensure we have a valid challenge message */
    if(!chlg) {
      infof(data, "SPNEGO handshake failure (empty challenge message)\n");

      return CURLE_BAD_CONTENT_ENCODING;
    }

    /* Setup the challenge "input" security buffer */
    chlg_desc.ulVersion = SECBUFFER_VERSION;
    chlg_desc.cBuffers  = 1;
    chlg_desc.pBuffers  = &chlg_buf;
    chlg_buf.BufferType = SECBUFFER_TOKEN;
    chlg_buf.pvBuffer   = chlg;
    chlg_buf.cbBuffer   = curlx_uztoul(chlglen);
  }