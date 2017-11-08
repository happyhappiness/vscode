void Curl_convert_init(struct Curl_easy *data)
{
#if defined(CURL_DOES_CONVERSIONS) && defined(HAVE_ICONV)
  /* conversion descriptors for iconv calls */
  data->outbound_cd = (iconv_t)-1;
  data->inbound_cd  = (iconv_t)-1;
  data->utf8_cd     = (iconv_t)-1;
#else
  (void)data;
#endif /* CURL_DOES_CONVERSIONS && HAVE_ICONV */
}