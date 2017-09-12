@@ -5868,7 +5868,8 @@ static int fwriteBulk(FILE *fp, robj *obj) {
     obj = getDecodedObject(obj);
     snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
     if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
-    if (fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0) goto err;
+    if (sdslen(obj->ptr) && fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0)
+        goto err;
     if (fwrite("\r\n",2,1,fp) == 0) goto err;
     decrRefCount(obj);
     return 1;
@@ -5997,7 +5998,7 @@ static int rewriteAppendOnlyFile(char *filename) {
             }
             /* Save the expire time */
             if (expiretime != -1) {
-                char cmd[]="*3\r\n$6\r\nEXPIRE\r\n";
+                char cmd[]="*3\r\n$8\r\nEXPIREAT\r\n";
                 /* If this key is already expired skip it */
                 if (expiretime < now) continue;
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
@@ -6026,7 +6027,7 @@ static int rewriteAppendOnlyFile(char *filename) {
 werr:
     fclose(fp);
     unlink(tmpfile);
-    redisLog(REDIS_WARNING,"Write error writing append only fileon disk: %s", strerror(errno));
+    redisLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     if (di) dictReleaseIterator(di);
     return REDIS_ERR;
 }