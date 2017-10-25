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
  struct HttpPost *httppost=NULL;
  struct HttpPost *last_post=NULL;
  struct HttpPost *post;
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

  form=getFormData(httppost, &size);

  FormInit(&formread, form);

  while(nread = FormReader(buffer, 1, sizeof(buffer), (FILE *)&formread)) {
    fwrite(buffer, nread, 1, stderr);
  }

  fprintf(stderr, "size: %d\n", size);

  return 0;
}