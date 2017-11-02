int test(char *URL)
{
  CURL *curl;
  CURLcode res=CURLE_OK;
  CURLFORMcode formrc;

  struct curl_httppost *formpost=NULL;
  struct curl_httppost *lastptr=NULL;
  struct WriteThis pooh;
  struct WriteThis pooh2;

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  pooh.readptr = data;
  pooh.sizeleft = strlen(data);

  /* Fill in the file upload field */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "sendfile",
                        CURLFORM_STREAM, &pooh,
                        CURLFORM_CONTENTSLENGTH, (long)pooh.sizeleft,
                        CURLFORM_FILENAME, "postit2.c",
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(1) = %d\n", (int)formrc);

  /* Now add the same data with another name and make it not look like
     a file upload but still using the callback */

  pooh2.readptr = data;
  pooh2.sizeleft = strlen(data);

  /* Fill in the file upload field */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "callbackdata",
                        CURLFORM_STREAM, &pooh2,
                        CURLFORM_CONTENTSLENGTH, (long)pooh2.sizeleft,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(1) = %d\n", (int)formrc);

  /* Fill in the filename field */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "filename",
#ifdef CURL_DOES_CONVERSIONS
                        /* ASCII representation with escape
                           sequences for non-ASCII platforms */
                        CURLFORM_COPYCONTENTS,
                           "\x70\x6f\x73\x74\x69\x74\x32\x2e\x63",
#else
                        CURLFORM_COPYCONTENTS, "postit2.c",
#endif
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(2) = %d\n", (int)formrc);

  /* Fill in a submit field too */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "submit",
#ifdef CURL_DOES_CONVERSIONS
                        /* ASCII representation with escape
                           sequences for non-ASCII platforms */
                        CURLFORM_COPYCONTENTS, "\x73\x65\x6e\x64",
#else
                        CURLFORM_COPYCONTENTS, "send",
#endif
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(3) = %d\n", (int)formrc);

  formrc = curl_formadd(&formpost, &lastptr,
                        CURLFORM_COPYNAME, "somename",
                        CURLFORM_BUFFER, "somefile.txt",
                        CURLFORM_BUFFERPTR, "blah blah",
                        CURLFORM_BUFFERLENGTH, (long)9,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(4) = %d\n", (int)formrc);

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_formfree(formpost);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

  /* Now specify we want to POST data */
  test_setopt(curl, CURLOPT_POST, 1L);

  /* Set the expected POST size */
  test_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)pooh.sizeleft);

  /* we want to use our own read function */
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);

  /* send a multi-part formpost */
  test_setopt(curl, CURLOPT_HTTPPOST, formpost);

  /* get verbose debug output please */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* include headers in the output */
  test_setopt(curl, CURLOPT_HEADER, 1L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  /* now cleanup the formpost chain */
  curl_formfree(formpost);

  return res;
}