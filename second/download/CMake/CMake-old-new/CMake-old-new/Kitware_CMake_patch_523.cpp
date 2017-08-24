@@ -54,6 +54,12 @@ int check_defines_CXX()
   result = 0;
   }
 # endif
+# ifdef DIRECTORY_DEF_DEBUG
+  {
+  fprintf(stderr, "DIRECTORY_DEF_DEBUG should not be defined in CXX\n");
+  result = 0;
+  }
+# endif
 # ifndef FILE_DEF_RELEASE
 #  ifndef PREPROCESS_XCODE
   {
@@ -68,6 +74,12 @@ int check_defines_CXX()
   result = 0;
   }
 # endif
+# ifndef DIRECTORY_DEF_RELEASE
+  {
+  fprintf(stderr, "DIRECTORY_DEF_RELEASE should be defined in CXX\n");
+  result = 0;
+  }
+# endif
 #endif
 #ifdef PREPROCESS_DEBUG
 # ifndef FILE_DEF_DEBUG
@@ -84,6 +96,12 @@ int check_defines_CXX()
   result = 0;
   }
 # endif
+# ifndef DIRECTORY_DEF_DEBUG
+  {
+  fprintf(stderr, "DIRECTORY_DEF_DEBUG should be defined in CXX\n");
+  result = 0;
+  }
+# endif
 # ifdef FILE_DEF_RELEASE
   {
   fprintf(stderr, "FILE_DEF_RELEASE should not be defined in CXX\n");
@@ -96,6 +114,12 @@ int check_defines_CXX()
   result = 0;
   }
 # endif
+# ifdef DIRECTORY_DEF_RELEASE
+  {
+  fprintf(stderr, "DIRECTORY_DEF_RELEASE should not be defined in CXX\n");
+  result = 0;
+  }
+# endif
 #endif
 #if defined(FILE_DEF_DEBUG) || defined(TARGET_DEF_DEBUG)
 # if !defined(FILE_DEF_DEBUG) || !defined(TARGET_DEF_DEBUG)
@@ -155,6 +179,12 @@ int check_defines_CXX()
   result = 0;
   }
 #endif
+#ifndef DIRECTORY_DEF
+  {
+  fprintf(stderr, "DIRECTORY_DEF not defined in CXX\n");
+  result = 0;
+  }
+#endif
 #ifndef OLD_DEF
   {
   fprintf(stderr, "OLD_DEF not defined in CXX\n");