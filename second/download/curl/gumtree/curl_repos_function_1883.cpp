void Curl_convert_close(struct SessionHandle *data)
{
#ifdef HAVE_ICONV
  /* close iconv conversion descriptors */
  if(data->inbound_cd != (iconv_t)-1) {
    iconv_close(data->inbound_cd);
  }
  if(data->outbound_cd != (iconv_t)-1) {
    iconv_close(data->outbound_cd);
  }
  if(data->utf8_cd != (iconv_t)-1) {
    iconv_close(data->utf8_cd);
  }
#else
  (void)data;
#endif /* HAVE_ICONV */
}