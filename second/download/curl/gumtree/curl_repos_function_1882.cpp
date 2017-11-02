void Curl_convert_setup(struct SessionHandle *data)
{
  data->inbound_cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                                CURL_ICONV_CODESET_OF_NETWORK);
  data->outbound_cd = iconv_open(CURL_ICONV_CODESET_OF_NETWORK,
                                 CURL_ICONV_CODESET_OF_HOST);
  data->utf8_cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                             CURL_ICONV_CODESET_FOR_UTF8);
}