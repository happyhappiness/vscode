static CURLcode my_conv_from_ebcdic_to_ascii(char *buffer, size_t length)
{
  char *tempptrin, *tempptrout;
  size_t bytes = length;
  int rc;
  tempptrin = tempptrout = buffer;
  rc = platform_e2a(&tempptrin, &bytes, &tempptrout, &bytes);
  if(rc == PLATFORM_CONV_OK) {
    return CURLE_OK;
  }
  else {
    return CURLE_CONV_FAILED;
  }
}