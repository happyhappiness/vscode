CURLcode Curl_convert_from_utf8(struct Curl_easy *data,
                                char *buffer, size_t length)
{
  if(data && data->set.convfromutf8) {
    /* use translation callback */
    CURLcode result = data->set.convfromutf8(buffer, length);
    if(result) {
      failf(data,
            "CURLOPT_CONV_FROM_UTF8_FUNCTION callback returned %d: %s",
            (int)result, curl_easy_strerror(result));
    }

    return result;
  }
  else {
#ifdef HAVE_ICONV
    /* do the translation ourselves */
    iconv_t tmpcd = (iconv_t) -1;
    iconv_t *cd = &tmpcd;
    char *input_ptr;
    char *output_ptr;
    size_t in_bytes, out_bytes, rc;

    /* open an iconv conversion descriptor if necessary */
    if(data)
      cd = &data->utf8_cd;
    if(*cd == (iconv_t)-1) {
      *cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                       CURL_ICONV_CODESET_FOR_UTF8);
      if(*cd == (iconv_t)-1) {
        failf(data,
              "The iconv_open(\"%s\", \"%s\") call failed with errno %i: %s",
              CURL_ICONV_CODESET_OF_HOST,
              CURL_ICONV_CODESET_FOR_UTF8,
              errno, strerror(errno));
        return CURLE_CONV_FAILED;
      }
    }
    /* call iconv */
    input_ptr = output_ptr = buffer;
    in_bytes = out_bytes = length;
    rc = iconv(*cd, &input_ptr, &in_bytes,
               &output_ptr, &out_bytes);
    if(!data)
      iconv_close(tmpcd);
    if((rc == ICONV_ERROR) || (in_bytes != 0)) {
      failf(data,
            "The Curl_convert_from_utf8 iconv call failed with errno %i: %s",
            errno, strerror(errno));
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

  return CURLE_OK;
}