     return APR_SUCCESS;
 }
 
 static void htdbm_usage(void)
 {
 
-#if APR_HAVE_CRYPT_H
+#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
 #define CRYPT_OPTION "d"
 #else
 #define CRYPT_OPTION ""
 #endif
     fprintf(stderr, "htdbm -- program for manipulating DBM password databases.\n\n");
     fprintf(stderr, "Usage: htdbm    [-cm"CRYPT_OPTION"pstvx] [-TDBTYPE] database username\n");
