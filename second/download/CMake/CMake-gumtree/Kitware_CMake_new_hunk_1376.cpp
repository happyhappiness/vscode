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



