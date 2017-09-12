@@ -190,7 +190,7 @@ int dsSet(redisDb *db, robj *key, robj *val) {
 
     len = dsKeyToPath(db,buf,key);
     memcpy(buf2,buf,len);
-    snprintf(buf2+len,sizeof(buf2)-len,"%ld.%ld",(long)time(NULL),(long)val);
+    snprintf(buf2+len,sizeof(buf2)-len,"_%ld_%ld",(long)time(NULL),(long)val);
     fp = fopen(buf2,"w");
     if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
         return REDIS_ERR;