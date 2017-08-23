@@ -33,7 +33,7 @@
 #include "urldata.h" /* for struct Curl_easy */
 #include "formdata.h"
 #include "vtls/vtls.h"
-#include "strequal.h"
+#include "strcase.h"
 #include "sendf.h"
 #include "strdup.h"
 /* The last 3 #include files should be in this order */
@@ -201,9 +201,9 @@ static const char *ContentTypeForFilename(const char *filename,
   if(filename) { /* in case a NULL was passed in */
     for(i=0; i<sizeof(ctts)/sizeof(ctts[0]); i++) {
       if(strlen(filename) >= strlen(ctts[i].extension)) {
-        if(strequal(filename +
-                    strlen(filename) - strlen(ctts[i].extension),
-                    ctts[i].extension)) {
+        if(strcasecompare(filename +
+                          strlen(filename) - strlen(ctts[i].extension),
+                          ctts[i].extension)) {
           contenttype = ctts[i].type;
           break;
         }
@@ -845,16 +845,23 @@ static CURLcode AddFormData(struct FormData **formp,
       goto error;
     }
 #endif
+    if(type != FORM_DATAMEM) {
+      newform->line = malloc((size_t)length+1);
+      if(!newform->line) {
+        result = CURLE_OUT_OF_MEMORY;
+        goto error;
+      }
+      alloc2 = newform->line;
+      memcpy(newform->line, line, (size_t)length);
 
-    newform->line = malloc((size_t)length+1);
-    if(!newform->line) {
-      result = CURLE_OUT_OF_MEMORY;
-      goto error;
+      /* zero terminate for easier debugging */
+      newform->line[(size_t)length]=0;
+    }
+    else {
+      newform->line = (char *)line;
+      type = FORM_DATA; /* in all other aspects this is just FORM_DATA */
     }
-    alloc2 = newform->line;
-    memcpy(newform->line, line, (size_t)length);
     newform->length = (size_t)length;
-    newform->line[(size_t)length]=0; /* zero terminate for easier debugging */
   }
   else
     /* For callbacks and files we don't have any actual data so we just keep a
@@ -863,13 +870,6 @@ static CURLcode AddFormData(struct FormData **formp,
 
   newform->type = type;
 
-  if(*formp) {
-    (*formp)->next = newform;
-    *formp = newform;
-  }
-  else
-    *formp = newform;
-
   if(size) {
     if(type != FORM_FILE)
       /* for static content as well as callback data we add the size given
@@ -878,7 +878,7 @@ static CURLcode AddFormData(struct FormData **formp,
     else {
       /* Since this is a file to be uploaded here, add the size of the actual
          file */
-      if(!strequal("-", newform->line)) {
+      if(strcmp("-", newform->line)) {
         struct_stat file;
         if(!stat(newform->line, &file) && !S_ISDIR(file.st_mode))
           *size += filesize(newform->line, file);
@@ -889,6 +889,14 @@ static CURLcode AddFormData(struct FormData **formp,
       }
     }
   }
+
+  if(*formp) {
+    (*formp)->next = newform;
+    *formp = newform;
+  }
+  else
+    *formp = newform;
+
   return CURLE_OK;
   error:
   if(newform)
@@ -906,13 +914,21 @@ static CURLcode AddFormDataf(struct FormData **formp,
                              curl_off_t *size,
                              const char *fmt, ...)
 {
-  char s[4096];
+  char *s;
+  CURLcode result;
   va_list ap;
   va_start(ap, fmt);
-  vsnprintf(s, sizeof(s), fmt, ap);
+  s = curl_mvaprintf(fmt, ap);
   va_end(ap);
 
-  return AddFormData(formp, FORM_DATA, s, 0, size);
+  if(!s)
+    return CURLE_OUT_OF_MEMORY;
+
+  result = AddFormData(formp, FORM_DATAMEM, s, 0, size);
+  if(result)
+    free(s);
+
+  return result;
 }
 
 /*
@@ -1289,7 +1305,7 @@ CURLcode Curl_getformdata(struct Curl_easy *data,
         /* we should include the contents from the specified file */
         FILE *fileread;
 
-        fileread = strequal("-", file->contents)?
+        fileread = !strcmp("-", file->contents)?
           stdin:fopen(file->contents, "rb"); /* binary read for win32  */
 
         /*