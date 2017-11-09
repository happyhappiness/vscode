int test(char *URL)
{
  unsigned char a[] = {0x2f, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
                       0x91, 0xa2, 0xb3, 0xc4, 0xd5, 0xe6, 0xf7};
  CURLcode res;
  CURL *curl;
  int asize;
  char *str = NULL;

  (void)URL;

  res = curl_global_init_mem(CURL_GLOBAL_ALL,
                             custom_malloc,
                             custom_free,
                             custom_realloc,
                             custom_strdup,
                             custom_calloc);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_global_init_mem() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  test_setopt(curl, CURLOPT_USERAGENT, "test509"); /* uses strdup() */

  asize = (int)sizeof(a);
  str = curl_easy_escape(curl, (char *)a, asize); /* uses realloc() */

test_cleanup:

  if(str)
    curl_free(str);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}