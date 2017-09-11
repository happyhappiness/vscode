@@ -143,6 +143,7 @@
 #define ZIPLIST_TAIL_OFFSET(zl) (*((uint32_t*)((zl)+sizeof(uint32_t))))
 #define ZIPLIST_LENGTH(zl)      (*((uint16_t*)((zl)+sizeof(uint32_t)*2)))
 #define ZIPLIST_HEADER_SIZE     (sizeof(uint32_t)*2+sizeof(uint16_t))
+#define ZIPLIST_END_SIZE        (sizeof(uint8_t))
 #define ZIPLIST_ENTRY_HEAD(zl)  ((zl)+ZIPLIST_HEADER_SIZE)
 #define ZIPLIST_ENTRY_TAIL(zl)  ((zl)+intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl)))
 #define ZIPLIST_ENTRY_END(zl)   ((zl)+intrev32ifbe(ZIPLIST_BYTES(zl))-1)
@@ -176,6 +177,8 @@ typedef struct zlentry {
     if ((encoding) < ZIP_STR_MASK) (encoding) &= ZIP_STR_MASK; \
 } while(0)
 
+void ziplistRepr(unsigned char *zl);
+
 /* Return bytes needed to store integer encoded by 'encoding' */
 static unsigned int zipIntSize(unsigned char encoding) {
     switch(encoding) {
@@ -670,6 +673,121 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
     return zl;
 }
 
+/* Merge ziplists 'first' and 'second' by appending 'second' to 'first'.
+ *
+ * NOTE: The larger ziplist is reallocated to contain the new merged ziplist.
+ * Either 'first' or 'second' can be used for the result.  The parameter not
+ * used will be free'd and set to NULL.
+ *
+ * After calling this function, the input parameters are no longer valid since
+ * they are changed and free'd in-place.
+ *
+ * The result ziplist is the contents of 'first' followed by 'second'.
+ *
+ * On failure: returns NULL if the merge is impossible.
+ * On success: returns the merged ziplist (which is expanded version of either
+ * 'first' or 'second', also frees the other unused input ziplist, and sets the
+ * input ziplist argument equal to newly reallocated ziplist return value. */
+unsigned char *ziplistMerge(unsigned char **first, unsigned char **second) {
+    /* If any params are null, we can't merge, so NULL. */
+    if (first == NULL || *first == NULL || second == NULL || *second == NULL)
+        return NULL;
+
+    /* Can't merge same list into itself. */
+    if (*first == *second)
+        return NULL;
+
+    size_t first_bytes = intrev32ifbe(ZIPLIST_BYTES(*first));
+    size_t first_len = intrev16ifbe(ZIPLIST_LENGTH(*first));
+
+    size_t second_bytes = intrev32ifbe(ZIPLIST_BYTES(*second));
+    size_t second_len = intrev16ifbe(ZIPLIST_LENGTH(*second));
+
+    int append;
+    unsigned char *source, *target;
+    size_t target_bytes, source_bytes;
+    /* Pick the largest ziplist so we can resize easily in-place.
+     * We must also track if we are now appending or prepending to
+     * the target ziplist. */
+    if (first_len >= second_len) {
+        /* retain first, append second to first. */
+        target = *first;
+        target_bytes = first_bytes;
+        source = *second;
+        source_bytes = second_bytes;
+        append = 1;
+    } else {
+        /* else, retain second, prepend first to second. */
+        target = *second;
+        target_bytes = second_bytes;
+        source = *first;
+        source_bytes = first_bytes;
+        append = 0;
+    }
+
+    /* Calculate final bytes (subtract one pair of metadata) */
+    size_t zlbytes = first_bytes + second_bytes -
+                     ZIPLIST_HEADER_SIZE - ZIPLIST_END_SIZE;
+    size_t zllength = first_len + second_len;
+
+    /* Combined zl length should be limited within UINT16_MAX */
+    zllength = zllength < UINT16_MAX ? zllength : UINT16_MAX;
+
+    /* Save offset positions before we start ripping memory apart. */
+    size_t first_offset = intrev32ifbe(ZIPLIST_TAIL_OFFSET(*first));
+    size_t second_offset = intrev32ifbe(ZIPLIST_TAIL_OFFSET(*second));
+
+    /* Extend target to new zlbytes then append or prepend source. */
+    target = zrealloc(target, zlbytes);
+    if (append) {
+        /* append == appending to target */
+        /* Copy source after target (copying over original [END]):
+         *   [TARGET - END, SOURCE - HEADER] */
+        memcpy(target + target_bytes - ZIPLIST_END_SIZE,
+               source + ZIPLIST_HEADER_SIZE,
+               source_bytes - ZIPLIST_HEADER_SIZE);
+    } else {
+        /* !append == prepending to target */
+        /* Move target *contents* exactly size of (source - [END]),
+         * then copy source into vacataed space (source - [END]):
+         *   [SOURCE - END, TARGET - HEADER] */
+        memmove(target + source_bytes - ZIPLIST_END_SIZE,
+                target + ZIPLIST_HEADER_SIZE,
+                target_bytes - ZIPLIST_HEADER_SIZE);
+        memcpy(target, source, source_bytes - ZIPLIST_END_SIZE);
+    }
+
+    /* Update header metadata. */
+    ZIPLIST_BYTES(target) = intrev32ifbe(zlbytes);
+    ZIPLIST_LENGTH(target) = intrev16ifbe(zllength);
+    /* New tail offset is:
+     *   + N bytes of first ziplist
+     *   - 1 byte for [END] of first ziplist
+     *   + M bytes for the offset of the original tail of the second ziplist
+     *   - J bytes for HEADER because second_offset keeps no header. */
+    ZIPLIST_TAIL_OFFSET(target) = intrev32ifbe(
+                                   (first_bytes - ZIPLIST_END_SIZE) +
+                                   (second_offset - ZIPLIST_HEADER_SIZE));
+
+    /* __ziplistCascadeUpdate just fixes the prev length values until it finds a
+     * correct prev length value (then it assumes the rest of the list is okay).
+     * We tell CascadeUpdate to start at the first ziplist's tail element to fix
+     * the merge seam. */
+    target = __ziplistCascadeUpdate(target, target+first_offset);
+
+    /* Now free and NULL out what we didn't realloc */
+    if (append) {
+        zfree(*second);
+        *second = NULL;
+        *first = target;
+    } else {
+        zfree(*first);
+        *first = NULL;
+        *second = target;
+    }
+    return target;
+}
+
 unsigned char *ziplistPush(unsigned char *zl, unsigned char *s, unsigned int slen, int where) {
     unsigned char *p;
     p = (where == ZIPLIST_HEAD) ? ZIPLIST_ENTRY_HEAD(zl) : ZIPLIST_ENTRY_END(zl);
@@ -1456,6 +1574,80 @@ int ziplistTest(int argc, char **argv) {
         printf("SUCCESS\n\n");
     }
 
+    printf("Merge test:\n");
+    {
+        /* create list gives us: [hello, foo, quux, 1024] */
+        zl = createList();
+        unsigned char *zl2 = createList();
+
+        unsigned char *zl3 = ziplistNew();
+        unsigned char *zl4 = ziplistNew();
+
+        if (ziplistMerge(&zl4, &zl4)) {
+            printf("ERROR: Allowed merging of one ziplist into itself.\n");
+            return 1;
+        }
+
+        /* Merge two empty ziplists, get empty result back. */
+        zl4 = ziplistMerge(&zl3, &zl4);
+        ziplistRepr(zl4);
+        if (ziplistLen(zl4)) {
+            printf("ERROR: Merging two empty ziplists created entries.\n");
+            return 1;
+        }
+        zfree(zl4);
+
+        zl2 = ziplistMerge(&zl, &zl2);
+        /* merge gives us: [hello, foo, quux, 1024, hello, foo, quux, 1024] */
+        ziplistRepr(zl2);
+
+        if (ziplistLen(zl2) != 8) {
+            printf("ERROR: Merged length not 8, but: %u\n", ziplistLen(zl2));
+            return 1;
+        }
+
+        p = ziplistIndex(zl2,0);
+        if (!ziplistCompare(p,(unsigned char*)"hello",5)) {
+            printf("ERROR: not \"hello\"\n");
+            return 1;
+        }
+        if (ziplistCompare(p,(unsigned char*)"hella",5)) {
+            printf("ERROR: \"hella\"\n");
+            return 1;
+        }
+
+        p = ziplistIndex(zl2,3);
+        if (!ziplistCompare(p,(unsigned char*)"1024",4)) {
+            printf("ERROR: not \"1024\"\n");
+            return 1;
+        }
+        if (ziplistCompare(p,(unsigned char*)"1025",4)) {
+            printf("ERROR: \"1025\"\n");
+            return 1;
+        }
+
+        p = ziplistIndex(zl2,4);
+        if (!ziplistCompare(p,(unsigned char*)"hello",5)) {
+            printf("ERROR: not \"hello\"\n");
+            return 1;
+        }
+        if (ziplistCompare(p,(unsigned char*)"hella",5)) {
+            printf("ERROR: \"hella\"\n");
+            return 1;
+        }
+
+        p = ziplistIndex(zl2,7);
+        if (!ziplistCompare(p,(unsigned char*)"1024",4)) {
+            printf("ERROR: not \"1024\"\n");
+            return 1;
+        }
+        if (ziplistCompare(p,(unsigned char*)"1025",4)) {
+            printf("ERROR: \"1025\"\n");
+            return 1;
+        }
+        printf("SUCCESS\n\n");
+    }
+
     printf("Stress with random payloads of different encoding:\n");
     {
         int i,j,len,where;