@@ -199,16 +199,19 @@ void SHA1Final(unsigned char digest[20], SHA1_CTX* context)
 }
 /* ================ end of sha1.c ================ */
 
-#if 0
+#ifdef REDIS_TEST
 #define BUFSIZE 4096
 
-int
-main(int argc, char **argv)
+#define UNUSED(x) (void)(x)
+int sha1Test(int argc, char **argv)
 {
     SHA1_CTX ctx;
     unsigned char hash[20], buf[BUFSIZE];
     int i;
 
+    UNUSED(argc);
+    UNUSED(argv);
+
     for(i=0;i<BUFSIZE;i++)
         buf[i] = i;
 
@@ -223,6 +226,4 @@ main(int argc, char **argv)
     printf("\n");
     return 0;
 }
-
 #endif
-