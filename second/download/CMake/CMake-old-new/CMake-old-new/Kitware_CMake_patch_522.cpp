@@ -52,6 +52,12 @@ int check_defines_C(void)
   result = 0;
   }
 # endif
+# ifdef DIRECTORY_DEF_DEBUG
+  {
+  fprintf(stderr, "DIRECTORY_DEF_DEBUG should not be defined in C\n");
+  result = 0;
+  }
+# endif
 # ifndef FILE_DEF_RELEASE
 #  ifndef PREPROCESS_XCODE
   {
@@ -66,6 +72,12 @@ int check_defines_C(void)
   result = 0;
   }
 # endif
+# ifndef DIRECTORY_DEF_RELEASE
+  {
+  fprintf(stderr, "DIRECTORY_DEF_RELEASE should be defined in C\n");
+  result = 0;
+  }
+# endif
 #endif
 #ifdef PREPROCESS_DEBUG
 # ifndef FILE_DEF_DEBUG
@@ -82,6 +94,12 @@ int check_defines_C(void)
   result = 0;
   }
 # endif
+# ifndef DIRECTORY_DEF_DEBUG
+  {
+  fprintf(stderr, "DIRECTORY_DEF_DEBUG should be defined in C\n");
+  result = 0;
+  }
+# endif
 # ifdef FILE_DEF_RELEASE
   {
   fprintf(stderr, "FILE_DEF_RELEASE should not be defined in C\n");
@@ -94,6 +112,12 @@ int check_defines_C(void)
   result = 0;
   }
 # endif
+# ifdef DIRECTORY_DEF_RELEASE
+  {
+  fprintf(stderr, "DIRECTORY_DEF_RELEASE should not be defined in C\n");
+  result = 0;
+  }
+# endif
 #endif
 #if defined(FILE_DEF_DEBUG) || defined(TARGET_DEF_DEBUG)
 # if !defined(FILE_DEF_DEBUG) || !defined(TARGET_DEF_DEBUG)
@@ -153,6 +177,12 @@ int check_defines_C(void)
   result = 0;
   }
 #endif
+#ifndef DIRECTORY_DEF
+  {
+  fprintf(stderr, "DIRECTORY_DEF not defined in C\n");
+  result = 0;
+  }
+#endif
 #ifndef OLD_DEF
   {
   fprintf(stderr, "OLD_DEF not defined in C\n");