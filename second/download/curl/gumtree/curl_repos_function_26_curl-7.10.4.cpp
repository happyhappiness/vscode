int main(int argc, char *argv[])
{
  URL_FILE *handle;
  int nread;
  char buffer[256];

  (void)argc;
  (void)argv;

  handle = url_fopen("http://curl.haxx.se/", "r");

  if(!handle) {
    printf("couldn't url_fopen()\n");
  }

  do {
    nread = url_fread(buffer, sizeof(buffer), 1, handle);

    printf("We got: %d bytes\n", nread);
  } while(nread);

  url_fclose(handle);

  return 0;
}