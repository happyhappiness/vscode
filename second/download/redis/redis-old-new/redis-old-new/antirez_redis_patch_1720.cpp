@@ -143,7 +143,7 @@ static void randomizeClientKey(client c) {
 
     for (i = 0; i < c->randlen; i++) {
         r = random() % config.randomkeys_keyspacelen;
-        snprintf(buf,sizeof(buf),"%012lu",r);
+        snprintf(buf,sizeof(buf),"%012zu",r);
         memcpy(c->randptr[i],buf,12);
     }
 }