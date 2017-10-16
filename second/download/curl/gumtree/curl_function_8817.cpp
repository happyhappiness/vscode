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
  }
  if(curlinfo->features) {
    unsigned int i;
    printf("Features: ");
    for(i = 0; i < sizeof(feats)/sizeof(feats[0]); i++) {
      if(curlinfo->features & feats[i].bitmask)
        printf("%s ", feats[i].name);
    }
#ifdef USE_METALINK
    printf("Metalink ");
#endif
    puts(""); /* newline */
  }
}