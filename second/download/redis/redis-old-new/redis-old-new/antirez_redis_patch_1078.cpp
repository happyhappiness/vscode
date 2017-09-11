@@ -152,13 +152,18 @@ static void resetClient(client c) {
 }
 
 static void randomizeClientKey(client c) {
-    char buf[32];
-    size_t i, r;
+    size_t i;
 
     for (i = 0; i < c->randlen; i++) {
-        r = random() % config.randomkeys_keyspacelen;
-        snprintf(buf,sizeof(buf),"%012zu",r);
-        memcpy(c->randptr[i],buf,12);
+        char *p = c->randptr[i]+11;
+        size_t r = random() % config.randomkeys_keyspacelen;
+        size_t j;
+
+        for (j = 0; j < 12; j++) {
+            *p = '0'+r%10;
+            r/=10;
+            p--;
+        }
     }
 }
 