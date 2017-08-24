{
    /* Base64 encode the response */
    result = Curl_base64_encode(data, (char *) resp_buf.pvBuffer,
                                resp_buf.cbBuffer, outptr, outlen);
  }