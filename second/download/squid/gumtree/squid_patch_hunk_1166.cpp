             peerDigestFetchAbort(fetch, buf, "internal status error");
             return -1;
         }
 
         fetch->state = DIGEST_READ_CBLOCK;
         return hdr_size;    /* Say how much data we read */
-    } else {
-        /* need more data, do we have space? */
+    }
 
-        if (size >= SM_PAGE_SIZE) {
-            peerDigestFetchAbort(fetch, buf, "stored header too big");
-            return -1;
-        } else {
-            return 0;       /* We need to read more to parse .. */
-        }
+    /* need more data, do we have space? */
+    if (size >= SM_PAGE_SIZE) {
+        peerDigestFetchAbort(fetch, buf, "stored header too big");
+        return -1;
     }
 
-    fatal("peerDigestSwapInHeaders() - shouldn't get here!\n");
-    return 0; /* keep gcc happy */
+    return 0;       /* We need to read more to parse .. */
 }
 
 int
 peerDigestSwapInCBlock(void *data, char *buf, ssize_t size)
 {
     DigestFetchState *fetch = (DigestFetchState *)data;
