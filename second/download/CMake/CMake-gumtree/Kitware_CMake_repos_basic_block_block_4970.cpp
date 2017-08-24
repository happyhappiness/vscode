{
  if(data->set.convfromnetwork) {
    /* use translation callback */
    CURLcode result = data->set.convfromnetwork(buffer, length);
    if(result) {
      failf(data,
            "CURLOPT_CONV_FROM_NETWORK_FUNCTION callback returned %d: %s",
            (int)result, curl_easy_strerror(result));
    }

    return result;
  }
  else {
#ifdef HAVE_ICONV
    /* do the translation ourselves */
    char *input_ptr, *output_ptr;
    size_t in_bytes, out_bytes, rc;
    int error;

    /* open an iconv conversion descriptor if necessary */
    if(data->inbound_cd == (iconv_t)-1) {
      data->inbound_cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                                    CURL_ICONV_CODESET_OF_NETWORK);
      if(data->inbound_cd == (iconv_t)-1) {
        error = ERRNO;
        failf(data,
              "The iconv_open(\"%s\", \"%s\") call failed with errno %i: %s",
              CURL_ICONV_CODESET_OF_HOST,
              CURL_ICONV_CODESET_OF_NETWORK,
              error, strerror(error));
        return CURLE_CONV_FAILED;
      }
    }
    /* call iconv */
    input_ptr = output_ptr = buffer;
    in_bytes = out_bytes = length;
    rc = iconv(data->inbound_cd, (const char **)&input_ptr, &in_bytes,
               &output_ptr, &out_bytes);
    if((rc == ICONV_ERROR) || (in_bytes != 0)) {
      error = ERRNO;
      failf(data,
            "Curl_convert_from_network iconv call failed with errno %i: %s",
            error, strerror(error));
      return CURLE_CONV_FAILED;
    }
#else
    failf(data, "CURLOPT_CONV_FROM_NETWORK_FUNCTION callback required");
    return CURLE_CONV_REQD;
#endif /* HAVE_ICONV */
  }

  return CURLE_OK;
}