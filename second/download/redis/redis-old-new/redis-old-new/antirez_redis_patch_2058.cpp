@@ -45,7 +45,7 @@
 
 /* Utility macros */
 #define ZIPLIST_BYTES(zl) (*((unsigned int*)(zl)))
-#define ZIPLIST_TAIL_OFFSET(zl) (*((zl)+sizeof(unsigned int)))
+#define ZIPLIST_TAIL_OFFSET(zl) (*((unsigned int*)((zl)+sizeof(unsigned int))))
 #define ZIPLIST_LENGTH(zl) (*((zl)+2*sizeof(unsigned int)))
 #define ZIPLIST_HEADER_SIZE (2*sizeof(unsigned int)+1)
 #define ZIPLIST_ENTRY_HEAD(zl) ((zl)+ZIPLIST_HEADER_SIZE)
@@ -853,6 +853,27 @@ int main(int argc, char **argv) {
         ziplistRepr(zl);
     }
 
+    printf("Create long list and check indices:\n");
+    {
+        zl = ziplistNew();
+        char buf[32];
+        int i,len;
+        for (i = 0; i < 1000; i++) {
+            len = sprintf(buf,"%d",i);
+            zl = ziplistPush(zl,buf,len,ZIPLIST_TAIL);
+        }
+        for (i = 0; i < 1000; i++) {
+            p = ziplistIndex(zl,i);
+            assert(ziplistGet(p,NULL,NULL,&value));
+            assert(i == value);
+
+            p = ziplistIndex(zl,-i-1);
+            assert(ziplistGet(p,NULL,NULL,&value));
+            assert(999-i == value);
+        }
+        printf("SUCCESS\n\n");
+    }
+
     printf("Compare strings with ziplist entries:\n");
     {
         zl = createList();