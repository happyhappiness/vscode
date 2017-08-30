  size_t base64Len;
  unsigned char *data;
  int dataLen;
  struct SessionHandle *handle = NULL;

#ifdef CURL_DOES_CONVERSIONS
  /* get a Curl handle so Curl_base64_encode can translate properly */
  handle = curl_easy_init();
  if(handle == NULL) {
    fprintf(stderr, "Error: curl_easy_init failed\n");
    return 0;
  }
#endif
  data = (unsigned char *)suck(&dataLen);
  base64Len = Curl_base64_encode(handle, data, dataLen, &base64);

  fprintf(stderr, "%d\n", base64Len);
  fprintf(stdout, "%s\n", base64);

  free(base64); free(data);
#ifdef CURL_DOES_CONVERSIONS
  curl_easy_cleanup(handle);
#endif
  return 0;
}
#endif
