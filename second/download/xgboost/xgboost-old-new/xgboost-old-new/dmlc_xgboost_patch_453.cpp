@@ -38,6 +38,7 @@ namespace xgboost{
     namespace utils{
         inline void Error(const char *msg){
             fprintf(stderr, "Error:%s\n", msg);
+            fflush(stderr);
             exit(-1);
         }
 
@@ -57,7 +58,8 @@ namespace xgboost{
         inline FILE *FopenCheck(const char *fname, const char *flag){
             FILE *fp = fopen64(fname, flag);
             if (fp == NULL){
-                fprintf(stderr, "can not open file \"%s\"\n", fname);
+                fprintf(stderr, "can not open file \"%s\" \n", fname);
+                fflush(stderr);
                 exit(-1);
             }
             return fp;