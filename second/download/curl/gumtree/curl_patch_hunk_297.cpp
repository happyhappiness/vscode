 
 #ifdef DPRINTF_DEBUG
 int main()
 {
   char buffer[129];
   char *ptr;
-#ifdef ENABLE_64BIT
-  long long one=99;
-  long long two=100;
-  long long test = 0x1000000000LL;
+#ifdef HAVE_LONG_LONG_TYPE
+  LONG_LONG_TYPE one=99;
+  LONG_LONG_TYPE two=100;
+  LONG_LONG_TYPE test = 0x1000000000LL;
   curl_mprintf("%lld %lld %lld\n", one, two, test);
 #endif
 
   curl_mprintf("%3d %5d\n", 10, 1998);
 
   ptr=curl_maprintf("test this then baby %s%s%s%s%s%s %d %d %d loser baby get a hit in yer face now!", "", "pretty long string pretty long string pretty long string pretty long string pretty long string", "/", "/", "/", "pretty long string", 1998, 1999, 2001);
