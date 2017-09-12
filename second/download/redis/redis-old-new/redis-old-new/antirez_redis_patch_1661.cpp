@@ -408,12 +408,17 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
             offset = p-zl;
             extra = rawlensize-next.prevrawlensize;
             zl = ziplistResize(zl,curlen+extra);
-            ZIPLIST_TAIL_OFFSET(zl) += extra;
             p = zl+offset;
 
-            /* Move the tail to the back. */
+            /* Current pointer and offset for next element. */
             np = p+rawlen;
             noffset = np-zl;
+
+            /* Update tail offset when next element is not the tail element. */
+            if ((zl+ZIPLIST_TAIL_OFFSET(zl)) != np)
+                ZIPLIST_TAIL_OFFSET(zl) += extra;
+
+            /* Move the tail to the back. */
             memmove(np+rawlensize,
                 np+next.prevrawlensize,
                 curlen-noffset-next.prevrawlensize-1);
@@ -889,7 +894,7 @@ void pop(unsigned char *zl, int where) {
     }
 }
 
-void randstring(char *target, unsigned int min, unsigned int max) {
+int randstring(char *target, unsigned int min, unsigned int max) {
     int p, len = min+rand()%(max-min+1);
     int minval, maxval;
     switch(rand() % 3) {
@@ -911,10 +916,9 @@ void randstring(char *target, unsigned int min, unsigned int max) {
 
     while(p < len)
         target[p++] = minval+rand()%(maxval-minval+1);
-    return;
+    return len;
 }
 
-
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
@@ -1247,6 +1251,7 @@ int main(int argc, char **argv) {
         int i,j,len,where;
         unsigned char *p;
         char buf[1024];
+        int buflen;
         list *ref;
         listNode *refnode;
 
@@ -1255,10 +1260,6 @@ int main(int argc, char **argv) {
         unsigned int slen;
         long long sval;
 
-        /* In the regression for the cascade bug, it was triggered
-         * with a random seed of 2. */
-        srand(2);
-
         for (i = 0; i < 20000; i++) {
             zl = ziplistNew();
             ref = listCreate();
@@ -1268,31 +1269,32 @@ int main(int argc, char **argv) {
             /* Create lists */
             for (j = 0; j < len; j++) {
                 where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
-                switch(rand() % 4) {
-                case 0:
-                    sprintf(buf,"%lld",(0LL + rand()) >> 20);
-                    break;
-                case 1:
-                    sprintf(buf,"%lld",(0LL + rand()));
-                    break;
-                case 2:
-                    sprintf(buf,"%lld",(0LL + rand()) << 20);
-                    break;
-                case 3:
-                    randstring(buf,0,256);
-                break;
-                default:
-                    assert(NULL);
+                if (rand() % 2) {
+                    buflen = randstring(buf,1,sizeof(buf)-1);
+                } else {
+                    switch(rand() % 3) {
+                    case 0:
+                        buflen = sprintf(buf,"%lld",(0LL + rand()) >> 20);
+                        break;
+                    case 1:
+                        buflen = sprintf(buf,"%lld",(0LL + rand()));
+                        break;
+                    case 2:
+                        buflen = sprintf(buf,"%lld",(0LL + rand()) << 20);
+                        break;
+                    default:
+                        assert(NULL);
+                    }
                 }
 
                 /* Add to ziplist */
-                zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);
+                zl = ziplistPush(zl, (unsigned char*)buf, buflen, where);
 
                 /* Add to reference list */
                 if (where == ZIPLIST_HEAD) {
-                    listAddNodeHead(ref,sdsnew(buf));
+                    listAddNodeHead(ref,sdsnewlen(buf, buflen));
                 } else if (where == ZIPLIST_TAIL) {
-                    listAddNodeTail(ref,sdsnew(buf));
+                    listAddNodeTail(ref,sdsnewlen(buf, buflen));
                 } else {
                     assert(NULL);
                 }
@@ -1307,12 +1309,13 @@ int main(int argc, char **argv) {
 
                 assert(ziplistGet(p,&sstr,&slen,&sval));
                 if (sstr == NULL) {
-                    sprintf(buf,"%lld",sval);
+                    buflen = sprintf(buf,"%lld",sval);
                 } else {
-                    memcpy(buf,sstr,slen);
-                    buf[slen] = '\0';
+                    buflen = slen;
+                    memcpy(buf,sstr,buflen);
+                    buf[buflen] = '\0';
                 }
-                assert(strcmp(buf,listNodeValue(refnode)) == 0);
+                assert(memcmp(buf,listNodeValue(refnode),buflen) == 0);
             }
             zfree(zl);
             listRelease(ref);