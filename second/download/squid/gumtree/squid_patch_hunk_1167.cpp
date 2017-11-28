             fetch->state = DIGEST_READ_MASK;
             return StoreDigestCBlockSize;
         } else {
             peerDigestFetchAbort(fetch, buf, "invalid digest cblock");
             return -1;
         }
-    } else {
-        /* need more data, do we have space? */
+    }
 
-        if (size >= SM_PAGE_SIZE) {
-            peerDigestFetchAbort(fetch, buf, "digest cblock too big");
-            return -1;
-        } else {
-            return 0;       /* We need more data */
-        }
+    /* need more data, do we have space? */
+    if (size >= SM_PAGE_SIZE) {
+        peerDigestFetchAbort(fetch, buf, "digest cblock too big");
+        return -1;
     }
 
-    fatal("peerDigestSwapInCBlock(): shouldn't get here!\n");
-    return 0; /* keep gcc happy */
+    return 0;       /* We need more data */
 }
 
 int
 peerDigestSwapInMask(void *data, char *buf, ssize_t size)
 {
     DigestFetchState *fetch = (DigestFetchState *)data;
