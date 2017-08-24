{
#ifdef HAVE_ICONV
    /* do the translation ourselves */
    const char *input_ptr;
    char *output_ptr;
    size_t in_bytes, out_bytes, rc;
    int error;

    /* open an iconv conversion descriptor if necessary */
    if(data->utf8_cd == (iconv_t)-1) {
      data->utf8_cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                                 CURL_ICONV_CODESET_FOR_UTF8);
      if(data->utf8_cd == (iconv_t)-1) {
        error = ERRNO;
        failf(data,
              "The iconv_open(\"%s\", \"%s\") call failed with errno %i: %s",
              CURL_ICONV_CODESET_OF_HOST,
              CURL_ICONV_CODESET_FOR_UTF8,
              error, strerror(error));
        return CURLE_CONV_FAILED;
      }
    }
    /* call iconv */
    input_ptr = output_ptr = buffer;
    in_bytes = out_bytes = length;
    rc = iconv(data->utf8_cd, &input_ptr, &in_bytes,
               &output_ptr, &out_bytes);
    if((rc == ICONV_ERROR) || (in_bytes != 0)) {
      error = ERRNO;
      failf(data,
            "The Curl_convert_from_utf8 iconv call failed with errno %i: %s",
            error, strerror(error));
      return CURLE_CONV_FAILED;
    }
    if(output_ptr < input_ptr) {
      /* null terminate the now shorter output string */
      *output_ptr = 0x00;
    }
#else
    failf(data, "CURLOPT_CONV_FROM_UTF8_FUNCTION callback required");
    return CURLE_CONV_REQD;
#endif /* HAVE_ICONV */
  }