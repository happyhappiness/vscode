int main(int argc, char *argv[])
{
  int arg=1;
  const char *host = NULL;
  int rc = 0;

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("resolve IPv4%s\n",
#ifdef ENABLE_IPV6
             "/IPv6"
#else
             ""
#endif
             );
      return 0;
    }
    else if(!strcmp("--ipv6", argv[arg])) {
      ipv_inuse = "IPv6";
      use_ipv6 = TRUE;
      arg++;
    }
    else if(!strcmp("--ipv4", argv[arg])) {
      /* for completeness, we support this option as well */
      ipv_inuse = "IPv4";
      use_ipv6 = FALSE;
      arg++;
    }
    else {
      host = argv[arg++];
    }
  }
  if(!host) {
    puts("Usage: resolve [option] <host>\n"
         " --version\n"
         " --ipv4"
#ifdef ENABLE_IPV6
         "\n --ipv6"
#endif
         );
    return 1;
  }

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);
#endif

  if(!use_ipv6) {
    /* gethostbyname() resolve */
    struct hostent *he;

    he = gethostbyname(host);

    rc = !he;
  }
  else {
#ifdef ENABLE_IPV6
    /* Check that the system has IPv6 enabled before checking the resolver */
    curl_socket_t s = socket(PF_INET6, SOCK_DGRAM, 0);
    if(s == CURL_SOCKET_BAD)
      /* an ipv6 address was requested and we can't get/use one */
      rc = -1;
    else {
      sclose(s);
    }

    if (rc == 0) {
      /* getaddrinfo() resolve */
      struct addrinfo *ai;
      struct addrinfo hints;

      memset(&hints, 0, sizeof(hints));
      hints.ai_family = PF_INET6;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_CANONNAME;
      /* Use parenthesis around function to stop it from being replaced by
      the macro in memdebug.h */
      rc = (getaddrinfo)(host, "80", &hints, &ai);
    }

#else
    puts("IPv6 support has been disabled in this program");
    return 1;
#endif
  }
  if(rc)
    printf("Resolving %s '%s' didn't work\n", ipv_inuse, host);

  return !!rc;
}