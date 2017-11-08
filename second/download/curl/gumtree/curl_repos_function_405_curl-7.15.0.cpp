int main()
{
  char name1[] = "simple_COPYCONTENTS";
  char name2[] = "COPYCONTENTS_+_CONTENTTYPE";
  char name3[] = "PTRNAME_+_NAMELENGTH_+_COPYNAME_+_CONTENTSLENGTH";
  char name4[] = "simple_PTRCONTENTS";
  char name5[] = "PTRCONTENTS_+_CONTENTSLENGTH";
  char name6[] = "PTRCONTENTS_+_CONTENTSLENGTH_+_CONTENTTYPE";
  char name7[] = "FILE1_+_CONTENTTYPE";
  char name8[] = "FILE1_+_FILE2";
  char name9[] = "FILE1_+_FILE2_+_FILE3";
  char name10[] = "ARRAY: FILE1_+_FILE2_+_FILE3";
  char name11[] = "FILECONTENT";
  char value1[] = "value for simple COPYCONTENTS";
  char value2[] = "value for COPYCONTENTS + CONTENTTYPE";
  char value3[] = "value for PTRNAME + NAMELENGTH + COPYNAME + CONTENTSLENGTH";
  char value4[] = "value for simple PTRCONTENTS";
  char value5[] = "value for PTRCONTENTS + CONTENTSLENGTH";
  char value6[] = "value for PTRCOTNENTS + CONTENTSLENGTH + CONTENTTYPE";
  char value7[] = "inet_ntoa_r.h";
  char value8[] = "Makefile.b32.resp";
  char type2[] = "image/gif";
  char type6[] = "text/plain";
  char type7[] = "text/html";
  int name3length = strlen(name3);
  int value3length = strlen(value3);
  int value5length = strlen(value4);
  int value6length = strlen(value5);
  int errors = 0;
  int size;
  size_t nread;
  char buffer[4096];
  struct curl_httppost *httppost=NULL;
  struct curl_httppost *last_post=NULL;
  struct curl_forms forms[4];

  struct FormData *form;
  struct Form formread;

  if (FormAddTest("simple COPYCONTENTS test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name1, CURLFORM_COPYCONTENTS, value1,
                  CURLFORM_END))
    ++errors;
  if (FormAddTest("COPYCONTENTS  + CONTENTTYPE test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name2, CURLFORM_COPYCONTENTS, value2,
                  CURLFORM_CONTENTTYPE, type2, CURLFORM_END))
    ++errors;
  /* make null character at start to check that contentslength works
     correctly */
  name3[1] = '\0';
  value3[1] = '\0';
  if (FormAddTest("PTRNAME + NAMELENGTH + COPYNAME + CONTENTSLENGTH test",
                  &httppost, &last_post,
                  CURLFORM_PTRNAME, name3, CURLFORM_COPYCONTENTS, value3,
                  CURLFORM_CONTENTSLENGTH, value3length,
                  CURLFORM_NAMELENGTH, name3length, CURLFORM_END))
    ++errors;
  if (FormAddTest("simple PTRCONTENTS test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name4, CURLFORM_PTRCONTENTS, value4,
                  CURLFORM_END))
    ++errors;
  /* make null character at start to check that contentslength works
     correctly */
  value5[1] = '\0';
  if (FormAddTest("PTRCONTENTS + CONTENTSLENGTH test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name5, CURLFORM_PTRCONTENTS, value5,
                  CURLFORM_CONTENTSLENGTH, value5length, CURLFORM_END))
    ++errors;
  /* make null character at start to check that contentslength works
     correctly */
  value6[1] = '\0';
  if (FormAddTest("PTRCONTENTS + CONTENTSLENGTH + CONTENTTYPE test",
                  &httppost, &last_post,
                  CURLFORM_COPYNAME, name6, CURLFORM_PTRCONTENTS, value6,
                  CURLFORM_CONTENTSLENGTH, value6length,
                  CURLFORM_CONTENTTYPE, type6, CURLFORM_END))
    ++errors;
  if (FormAddTest("FILE + CONTENTTYPE test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name7, CURLFORM_FILE, value7,
                  CURLFORM_CONTENTTYPE, type7, CURLFORM_END))
    ++errors;
  if (FormAddTest("FILE1 + FILE2 test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name8, CURLFORM_FILE, value7,
                  CURLFORM_FILE, value8, CURLFORM_END))
    ++errors;
  if (FormAddTest("FILE1 + FILE2 + FILE3 test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name9, CURLFORM_FILE, value7,
                  CURLFORM_FILE, value8, CURLFORM_FILE, value7, CURLFORM_END))
    ++errors;
  forms[0].option = CURLFORM_FILE;
  forms[0].value  = value7;
  forms[1].option = CURLFORM_FILE;
  forms[1].value  = value8;
  forms[2].option = CURLFORM_FILE;
  forms[2].value  = value7;
  forms[3].option  = CURLFORM_END;
  if (FormAddTest("FILE1 + FILE2 + FILE3 ARRAY test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name10, CURLFORM_ARRAY, forms,
                  CURLFORM_END))
    ++errors;
  if (FormAddTest("FILECONTENT test", &httppost, &last_post,
                  CURLFORM_COPYNAME, name11, CURLFORM_FILECONTENT, value7,
                  CURLFORM_END))
    ++errors;

  form=Curl_getFormData(httppost, &size);

  Curl_FormInit(&formread, form);

  do {
    nread = Curl_FormReader(buffer, 1, sizeof(buffer),
                            (FILE *)&formread);

    if(-1 == nread)
      break;
    fwrite(buffer, nread, 1, stdout);
  } while(1);

  fprintf(stdout, "size: %d\n", size);
  if (errors)
    fprintf(stdout, "\n==> %d Test(s) failed!\n", errors);
  else
    fprintf(stdout, "\nAll Tests seem to have worked (please check output)\n");

  return 0;
}