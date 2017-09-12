@@ -144,7 +144,7 @@ static unsigned int zipDecodeLength(unsigned char *p, unsigned int *lensize) {
             if (lensize) *lensize = 1;
             break;
         case ZIP_STR_14B:
-            len = ((p[0] & 0x3f) << 6) | p[1];
+            len = ((p[0] & 0x3f) << 8) | p[1];
             if (lensize) *lensize = 2;
             break;
         case ZIP_STR_32B:
@@ -1125,6 +1125,25 @@ int main(int argc, char **argv) {
         ziplistRepr(zl);
     }
 
+    printf("Regression test for >255 byte strings:\n");
+    {
+        char v1[257],v2[257];
+        memset(v1,'x',256);
+        memset(v2,'y',256);
+        zl = ziplistNew();
+        zl = ziplistPush(zl,(unsigned char*)v1,strlen(v1),ZIPLIST_TAIL);
+        zl = ziplistPush(zl,(unsigned char*)v2,strlen(v2),ZIPLIST_TAIL);
+
+        /* Pop values again and compare their value. */
+        p = ziplistIndex(zl,0);
+        assert(ziplistGet(p,&entry,&elen,&value));
+        assert(strncmp(v1,entry,elen) == 0);
+        p = ziplistIndex(zl,1);
+        assert(ziplistGet(p,&entry,&elen,&value));
+        assert(strncmp(v2,entry,elen) == 0);
+        printf("SUCCESS\n\n");
+    }
+
     printf("Create long list and check indices:\n");
     {
         zl = ziplistNew();