#endif

#ifdef __SYMBIAN32__
#  define PRINT_LINES_PAUSE 16
#endif

struct feat {
  const char *name;
  int bitmask;
};

static const struct feat feats[] = {
  {"AsynchDNS",      CURL_VERSION_ASYNCHDNS},
  {"Debug",          CURL_VERSION_DEBUG},
  {"TrackMemory",    CURL_VERSION_CURLDEBUG},
  {"GSS-Negotiate",  CURL_VERSION_GSSNEGOTIATE},
  {"IDN",            CURL_VERSION_IDN},
  {"IPv6",           CURL_VERSION_IPV6},
  {"Largefile",      CURL_VERSION_LARGEFILE},
  {"NTLM",           CURL_VERSION_NTLM},
  {"NTLM_WB",        CURL_VERSION_NTLM_WB},
  {"SPNEGO",         CURL_VERSION_SPNEGO},
  {"SSL",            CURL_VERSION_SSL},
  {"SSPI",           CURL_VERSION_SSPI},
  {"krb4",           CURL_VERSION_KERBEROS4},
  {"libz",           CURL_VERSION_LIBZ},
  {"CharConv",       CURL_VERSION_CONV},
  {"TLS-SRP",        CURL_VERSION_TLSAUTH_SRP},
  {"HTTP2",          CURL_VERSION_HTTP2}
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

void tool_list_engines(CURL *curl)
{
  struct curl_slist *engines = NULL;

  /* Get the list of engines */
  curl_easy_getinfo(curl, CURLINFO_SSL_ENGINES, &engines);

  puts("Build-time engines:");
  if(engines) {
    for(; engines; engines = engines->next)
      printf("  %s\n", engines->data);
  }
  else {
    puts("  <none>");
  }

  /* Cleanup the list of engines */
  curl_slist_free_all(engines);
}
