@@ -163,12 +163,9 @@ void computeDatasetDigest(unsigned char *final) {
                 listTypeReleaseIterator(li);
             } else if (o->type == OBJ_SET) {
                 setTypeIterator *si = setTypeInitIterator(o);
-                robj *ele;
                 sds sdsele;
                 while((sdsele = setTypeNextObject(si)) != NULL) {
-                    ele = createObject(OBJ_STRING,sdsele);
-                    xorObjectDigest(digest,ele);
-                    decrRefCount(ele);
+                    xorDigest(digest,sdsele,sdslen(sdsele));
                 }
                 setTypeReleaseIterator(si);
             } else if (o->type == OBJ_ZSET) {
@@ -210,12 +207,12 @@ void computeDatasetDigest(unsigned char *final) {
                     dictEntry *de;
 
                     while((de = dictNext(di)) != NULL) {
-                        robj *eleobj = dictGetKey(de);
+                        sds sdsele = dictGetKey(de);
                         double *score = dictGetVal(de);
 
                         snprintf(buf,sizeof(buf),"%.17g",*score);
                         memset(eledigest,0,20);
-                        mixObjectDigest(eledigest,eleobj);
+                        mixDigest(eledigest,sdsele,sdslen(sdsele));
                         mixDigest(eledigest,buf,strlen(buf));
                         xorDigest(digest,eledigest,20);
                     }