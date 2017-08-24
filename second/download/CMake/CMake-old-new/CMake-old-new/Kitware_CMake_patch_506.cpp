@@ -11,7 +11,6 @@ extern "C" int check_defines_C(void);
 int check_defines_CXX()
 {
   int result = 1;
-#ifndef PREPROCESS_VS6
   if(strcmp(FILE_STRING, STRING_VALUE) != 0)
     {
     fprintf(stderr,
@@ -40,7 +39,6 @@ int check_defines_CXX()
     result = 0;
     }
   }
-#endif
 #ifdef NDEBUG
 # ifdef FILE_DEF_DEBUG
   {