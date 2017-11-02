void convert_cleanup(void)
{
  /* close iconv conversion descriptors */
  if(inbound_cd != (iconv_t)-1)
    (void)iconv_close(inbound_cd);
  if(outbound_cd != (iconv_t)-1)
    (void)iconv_close(outbound_cd);
}