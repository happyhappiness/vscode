@@ -191,7 +191,16 @@ int dsSet(redisDb *db, robj *key, robj *val) {
     len = dsKeyToPath(db,buf,key);
     memcpy(buf2,buf,len);
     snprintf(buf2+len,sizeof(buf2)-len,"_%ld_%ld",(long)time(NULL),(long)val);
-    fp = fopen(buf2,"w");
+    while ((fp = fopen(buf2,"w")) == NULL) {
+        if (errno == ENOSPC) {
+            redisLog(REDIS_WARNING,"Diskstore: No space left on device. Please make room and wait 30 seconds for Redis to continue.");
+            sleep(30);
+        } else {
+            redisLog(REDIS_WARNING,"diskstore error opening %s: %s",
+                buf2, strerror(errno));
+            redisPanic("Unrecoverable diskstore error. Exiting.");
+        }
+    }
     if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
         return REDIS_ERR;
     fclose(fp);