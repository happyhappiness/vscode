@@ -9,7 +9,6 @@
 int check_defines_C(void)
 {
   int result = 1;
-#ifndef PREPROCESS_VS6
   if(strcmp(FILE_STRING, STRING_VALUE) != 0)
     {
     fprintf(stderr,
@@ -38,7 +37,6 @@ int check_defines_C(void)
     result = 0;
     }
   }
-#endif
 #ifdef NDEBUG
 # ifdef FILE_DEF_DEBUG
   {