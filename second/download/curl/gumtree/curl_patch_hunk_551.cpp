 }
 
 int curl_mvfprintf(FILE *whereto, const char *format, va_list ap_save)
 {
   return dprintf_formatf(whereto, fputc, format, ap_save);
 }
-
-#ifdef DPRINTF_DEBUG
-int main()
-{
-  char buffer[129];
-  char *ptr;
-#ifdef HAVE_LONG_LONG_TYPE
-  LONG_LONG_TYPE one=99;
-  LONG_LONG_TYPE two=100;
-  LONG_LONG_TYPE test = 0x1000000000LL;
-  curl_mprintf("%lld %lld %lld\n", one, two, test);
-#endif
-
-  curl_mprintf("%3d %5d\n", 10, 1998);
-
-  ptr=curl_maprintf("test this then baby %s%s%s%s%s%s %d %d %d loser baby get a kiss in yer face now!", "", "pretty long string pretty long string pretty long string pretty long string pretty long string", "/", "/", "/", "pretty long string", 1998, 1999, 2001);
-
-  puts(ptr);
-
-  memset(ptr, 55, strlen(ptr)+1);
-
-  free(ptr);
-
-#if 1
-  curl_mprintf(buffer, "%s %s %d", "daniel", "stenberg", 19988);
-  puts(buffer);
-
-  curl_mfprintf(stderr, "%s %#08x\n", "dummy", 65);
-
-  printf("%s %#08x\n", "dummy", 65);
-  {
-    double tryout = 3.14156592;
-    curl_mprintf(buffer, "%.2g %G %f %e %E", tryout, tryout, tryout, tryout, tryout);
-    puts(buffer);
-    printf("%.2g %G %f %e %E\n", tryout, tryout, tryout, tryout, tryout);
-  }
-#endif
-
-  return 0;
-}
-
-#endif
