  {"HTTPS-proxy",    CURL_VERSION_HTTPS_PROXY}
};

void tool_help(void)
{
  int i;
  for(i = 0; helptext[i]; i++) {
    puts(helptext[i]);
#ifdef PRINT_LINES_PAUSE
    if(i && ((i % PRINT_LINES_PAUSE) == 0))
      tool_pressanykey();
#endif
  }
}

void tool_version_info(void)
{
  const char *const *proto;

  printf(CURL_ID "%s\n", curl_version());
  if(curlinfo->protocols) {
    printf("Protocols: ");
    for(proto = curlinfo->protocols; *proto; ++proto) {
      printf("%s ", *proto);
    }
    puts(""); /* newline */
