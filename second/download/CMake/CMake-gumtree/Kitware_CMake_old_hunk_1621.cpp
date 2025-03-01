
#endif

#ifdef _OLD_FORM_DEBUG

int main(int argc, char **argv)
{
#if 0
  char *testargs[]={
    "name1 = data in number one",
    "name2 = number two data",
    "test = @upload"
  };
#endif
  int i;
  char *nextarg;
  struct curl_httppost *httppost=NULL;
  struct curl_httppost *last_post=NULL;
  struct curl_httppost *post;
  int size;
  int nread;
  char buffer[4096];

  struct FormData *form;
  struct Form formread;

  for(i=1; i<argc; i++) {

    if( FormParse( argv[i],
                   &httppost,
                   &last_post)) {
      fprintf(stderr, "Illegally formatted input field: '%s'!\n",
              argv[i]);
      return 1;
    }
  }

  form=Curl_getFormData(httppost, &size);

  Curl_FormInit(&formread, form);

  do {
    nread = Curl_FormReader(buffer, 1, sizeof(buffer),
                            (FILE *)&formread);

    if(-1 == nread)
      break;
    fwrite(buffer, nread, 1, stderr);
  } while(1);

  fprintf(stderr, "size: %d\n", size);

  return 0;
}

#endif

#endif /* CURL_DISABLE_HTTP */

/*
 * local variables:
 * eval: (load-file "../curl-mode.el")
 * end:
 * vim600: fdm=marker
 * vim: et sw=2 ts=2 sts=2 tw=78
 */
