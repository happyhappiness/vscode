{
    if(output_token.value)
      gss_release_buffer(&unused_status, &output_token);

    return CURLE_OUT_OF_MEMORY;
  }