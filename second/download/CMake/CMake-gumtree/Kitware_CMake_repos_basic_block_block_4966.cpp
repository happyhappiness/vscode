{
#ifdef HAVE_ICONV
    /* do the translation ourselves */
    char *input_ptr, *output_ptr;
    size_t in_bytes, out_bytes, rc;
    int error;

    /* open an iconv conversion descriptor if necessary */
    if(data->outbound_cd == (iconv_t)-1) {
      data->outbound_cd = iconv_open(CURL_ICONV_CODESET_OF_NETWORK,
                                     CURL_ICONV_CODESET_OF_HOST);
      if(data->outbound_cd == (iconv_t)-1) {
        error = ERRNO;
        failf(data,
              "The iconv_open(\"%s\", \"%s\") call failed with errno %i: %s",
              CURL_ICONV_CODESET_OF_NETWORK,
              CURL_ICONV_CODESET_OF_HOST,
              error, strerror(error));
        return CURLE_CONV_FAILED;
      }
    }
    /* call iconv */
    input_ptr = output_ptr = buffer;
    in_bytes = out_bytes = length;
    rc = iconv(data->outbound_cd, (const char **)&input_ptr, &in_bytes,
               &output_ptr, &out_bytes);
    if((rc == ICONV_ERROR) || (in_bytes != 0)) {
      error = ERRNO;
      failf(data,
            "The Curl_convert_to_network iconv call failed with errno %i: %s",
            error, strerror(error));
      return CURLE_CONV_FAILED;
    }
#else
    failf(data, "CURLOPT_CONV_TO_NETWORK_FUNCTION callback required");
    return CURLE_CONV_REQD;
#endif /* HAVE_ICONV */
  }