int main(int argc, char **argv, char **envp)
{
  char *base64;
  int base64Len;
  unsigned char *data;
  int dataLen;
  int i, j;
#ifdef CURL_DOES_CONVERSIONS
  /* get a Curl handle so main can translate properly */
  struct SessionHandle *handle = curl_easy_init();
  if(handle == NULL) {
    fprintf(stderr, "Error: curl_easy_init failed\n");
    return 0;
  }
#endif

  base64 = (char *)suck(&base64Len);
  dataLen = Curl_base64_decode(base64, &data);

  fprintf(stderr, "%d\n", dataLen);

  for(i=0; i < dataLen; i+=0x10) {
    printf("0x%02x: ", i);
    for(j=0; j < 0x10; j++)
      if((j+i) < dataLen)
        printf("%02x ", data[i+j]);
      else
        printf("   ");

    printf(" | ");

    for(j=0; j < 0x10; j++)
      if((j+i) < dataLen) {
#ifdef CURL_DOES_CONVERSIONS
        if(CURLE_OK !=
             Curl_convert_from_network(handle, &data[i+j], (size_t)1))
          data[i+j] = '.';
#endif /* CURL_DOES_CONVERSIONS */
        printf("%c", ISGRAPH(data[i+j])?data[i+j]:'.');
      } else
        break;
    puts("");
  }

#ifdef CURL_DOES_CONVERSIONS
  curl_easy_cleanup(handle);
#endif
  free(base64); free(data);
  return 0;
}