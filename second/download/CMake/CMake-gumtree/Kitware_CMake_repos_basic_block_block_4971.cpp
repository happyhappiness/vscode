{
        error = ERRNO;
        failf(data,
              "The iconv_open(\"%s\", \"%s\") call failed with errno %i: %s",
              CURL_ICONV_CODESET_OF_HOST,
              CURL_ICONV_CODESET_OF_NETWORK,
              error, strerror(error));
        return CURLE_CONV_FAILED;
      }