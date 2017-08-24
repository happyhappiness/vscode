{
  CURLcode result;
  OM_uint32 minor_status;

  /* Base64 encode the already generated response */
  result = Curl_base64_encode(data,
                              nego->output_token.value,
                              nego->output_token.length,
                              outptr, outlen);

  if(result) {
    gss_release_buffer(&minor_status, &nego->output_token);
    nego->output_token.value = NULL;
    nego->output_token.length = 0;

    return result;
  }

  if(!*outptr || !*outlen) {
    gss_release_buffer(&minor_status, &nego->output_token);
    nego->output_token.value = NULL;
    nego->output_token.length = 0;

    return CURLE_REMOTE_ACCESS_DENIED;
  }

  return CURLE_OK;
}