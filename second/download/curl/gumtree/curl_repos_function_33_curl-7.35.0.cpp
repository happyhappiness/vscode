CURLcode my_conv_from_utf8_to_ebcdic(char *buffer, size_t length)
{
    char *tempptrin, *tempptrout;
    size_t bytes = length;
    int rc;
    tempptrin = tempptrout = buffer;
    rc = platform_u2e(&tempptrin, &bytes, &tempptrout, &bytes);
    if (rc == PLATFORM_CONV_OK) {
      return(CURLE_OK);
    } else {
      return(CURLE_CONV_FAILED);
    }
}