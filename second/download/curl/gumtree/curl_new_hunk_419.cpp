  LONG_LONG_TYPE test = 0x1000000000LL;
  curl_mprintf("%lld %lld %lld\n", one, two, test);
#endif

  curl_mprintf("%3d %5d\n", 10, 1998);

  ptr=curl_maprintf("test this then baby %s%s%s%s%s%s %d %d %d loser baby get a kiss in yer face now!", "", "pretty long string pretty long string pretty long string pretty long string pretty long string", "/", "/", "/", "pretty long string", 1998, 1999, 2001);

  puts(ptr);

  memset(ptr, 55, strlen(ptr)+1);

  free(ptr);
