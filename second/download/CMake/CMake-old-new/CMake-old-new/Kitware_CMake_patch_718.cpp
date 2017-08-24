@@ -41,6 +41,7 @@ char *curl_escape(const char *string, int length)
 {
   int alloc = (length?length:(int)strlen(string))+1;  
   char *ns = malloc(alloc);
+  char *testing_ptr = NULL;
   unsigned char in;
   int newlen = alloc;
   int index=0;
@@ -55,9 +56,14 @@ char *curl_escape(const char *string, int length)
       newlen += 2; /* the size grows with two, since this'll become a %XX */
       if(newlen > alloc) {
         alloc *= 2;
-        ns = realloc(ns, alloc);
-        if(!ns)
+        testing_ptr = realloc(ns, alloc);
+        if(!testing_ptr) {
+          free( ns );
           return NULL;
+        }
+        else {
+          ns = testing_ptr;
+        }
       }
       sprintf(&ns[index], "%%%02X", in);
 
@@ -80,6 +86,10 @@ char *curl_unescape(const char *string, int length)
   unsigned char in;
   int index=0;
   unsigned int hex;
+ 
+  if( !ns ) {
+    return NULL;
+  }  
   
   while(--alloc > 0) {
     in = *string;
@@ -97,7 +107,6 @@ char *curl_unescape(const char *string, int length)
   }
   ns[index]=0; /* terminate it */
   return ns;
-  
 }
 
 void curl_free(void *p)