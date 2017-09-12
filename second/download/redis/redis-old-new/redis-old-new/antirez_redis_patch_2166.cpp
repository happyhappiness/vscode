@@ -8318,6 +8318,38 @@ static double computeObjectSwappability(robj *o) {
             if (z) asize += sizeof(zskiplistNode)*dictSize(d);
         }
         break;
+    case REDIS_HASH:
+        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+            unsigned char *p = zipmapRewind((unsigned char*)o->ptr);
+            unsigned int len = zipmapLen((unsigned char*)o->ptr);
+            unsigned int klen, vlen;
+            unsigned char *key, *val;
+
+            if ((p = zipmapNext(p,&key,&klen,&val,&vlen)) == NULL) {
+                klen = 0;
+                vlen = 0;
+            }
+            asize = len*(klen+vlen+3);
+        } else if (o->encoding == REDIS_ENCODING_HT) {
+            d = o->ptr;
+            asize = sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
+            if (dictSize(d)) {
+                long elesize;
+                robj *ele;
+
+                de = dictGetRandomKey(d);
+                ele = dictGetEntryKey(de);
+                elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
+                                (sizeof(*o)+sdslen(ele->ptr)) :
+                                sizeof(*o);
+                ele = dictGetEntryVal(de);
+                elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
+                                (sizeof(*o)+sdslen(ele->ptr)) :
+                                sizeof(*o);
+                asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
+            }
+        }
+        break;
     }
     return (double)age*log(1+asize);
 }
@@ -8720,13 +8752,18 @@ static void *IOThreadEntryPoint(void *arg) {
 static void spawnIOThread(void) {
     pthread_t thread;
     sigset_t mask, omask;
+    int err;
 
     sigemptyset(&mask);
     sigaddset(&mask,SIGCHLD);
     sigaddset(&mask,SIGHUP);
     sigaddset(&mask,SIGPIPE);
     pthread_sigmask(SIG_SETMASK, &mask, &omask);
-    pthread_create(&thread,&server.io_threads_attr,IOThreadEntryPoint,NULL);
+    while ((err = pthread_create(&thread,&server.io_threads_attr,IOThreadEntryPoint,NULL)) != 0) {
+        redisLog(REDIS_WARNING,"Unable to spawn an I/O thread: %s",
+            strerror(err));
+        usleep(1000000);
+    }
     pthread_sigmask(SIG_SETMASK, &omask, NULL);
     server.io_active_threads++;
 }