  int base64Len;

  unsigned char *data;

  int dataLen;

        

  base64 = (char *)suck(&base64Len);

  data = (unsigned char *)malloc(base64Len * 3/4 + 8);

  dataLen = Curl_base64_decode(base64, data);

  

  fprintf(stderr, "%d\n", dataLen);

  fwrite(data,1,dataLen,stdout);

  

  free(base64); free(data);

  return 0;

}

