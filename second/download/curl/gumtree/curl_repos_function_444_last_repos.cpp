int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  CURLFORMcode formrc;
  struct curl_slist *headers = NULL;
  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct curl_forms formarray[3];
  size_t formlength = 0;
  char flbuf[32];

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* Check proper name and data copying. */
  formrc = curl_formadd(&formpost, &lastptr,
                        CURLFORM_COPYNAME, &name,
                        CURLFORM_COPYCONTENTS, &data,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(1) = %d\n", (int) formrc);

  /* Use a form array for the non-copy test. */
  formarray[0].option = CURLFORM_PTRCONTENTS;
  formarray[0].value = data;
  formarray[1].option = CURLFORM_CONTENTSLENGTH;
  formarray[1].value = (char *) strlen(data) - 1;
  formarray[2].option = CURLFORM_END;
  formarray[2].value = NULL;
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_PTRNAME, name,
                        CURLFORM_NAMELENGTH, strlen(name) - 1,
                        CURLFORM_ARRAY, formarray,
                        CURLFORM_FILENAME, "remotefile.txt",
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(2) = %d\n", (int) formrc);

  /* Now change in-memory data to affect CURLOPT_PTRCONTENTS value.
     Copied values (first field) must not be affected.
     CURLOPT_PTRNAME actually copies the name thus we do not test this here. */
  data[0]++;

  /* Check multi-files and content type propagation. */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "multifile",
                        CURLFORM_FILE, libtest_arg2,    /* Set in first.c. */
                        CURLFORM_FILE, libtest_arg2,
                        CURLFORM_CONTENTTYPE, "text/whatever",
                        CURLFORM_FILE, libtest_arg2,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(3) = %d\n", (int) formrc);

  /* Check data from file content and headers. */
  headers = curl_slist_append(headers, "X-customheader-1: Header 1 data");
  headers = curl_slist_append(headers, "X-customheader-2: Header 2 data");
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "filecontents",
                        CURLFORM_FILECONTENT, libtest_arg2,
                        CURLFORM_CONTENTHEADER, headers,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(3) = %d\n", (int) formrc);

  /* Measure the current form length.
   * This is done before including stdin data because we want to reuse it
   * and stdin cannot be rewound.
   */
  curl_formget(formpost, (void *) &formlength, count_chars);

  /* Include length in data for external check. */
  curl_msnprintf(flbuf, sizeof flbuf, "%lu", (unsigned long) formlength);
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "formlength",
                        CURLFORM_COPYCONTENTS, &flbuf,
                        CURLFORM_END);

  /* Check stdin (may be problematic on some platforms). */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "standardinput",
                        CURLFORM_FILE, "-",
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(4) = %d\n", (int) formrc);

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_slist_free_all(headers);
    curl_formfree(formpost);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

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

  /* now cleanup the formpost chain */
  curl_formfree(formpost);
  curl_slist_free_all(headers);

  curl_global_cleanup();

  return res;
}