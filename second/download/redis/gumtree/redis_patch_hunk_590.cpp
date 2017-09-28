  * printf("%d\n", sdslen(s));
  *
  * The output will be "2", but if we comment out the call to sdsupdatelen()
  * the output will be "6" as the string was modified but the logical length
  * remains 6 bytes. */
 void sdsupdatelen(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     int reallen = strlen(s);
-    sh->free += (sh->len-reallen);
-    sh->len = reallen;
+    sdssetlen(s, reallen);
 }
 
 /* Modify an sds string in-place to make it empty (zero length).
  * However all the existing buffer is not discarded but set as free space
  * so that next append operations will not require allocations up to the
  * number of bytes previously available. */
 void sdsclear(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
-    sh->free += sh->len;
-    sh->len = 0;
-    sh->buf[0] = '\0';
+    sdssetlen(s, 0);
+    s[0] = '\0';
 }
 
 /* Enlarge the free space at the end of the sds string so that the caller
  * is sure that after calling this function can overwrite up to addlen
  * bytes after the end of the string, plus one more byte for nul term.
  *
  * Note: this does not change the *length* of the sds string as returned
  * by sdslen(), but only the free buffer space we have. */
 sds sdsMakeRoomFor(sds s, size_t addlen) {
-    struct sdshdr *sh, *newsh;
-    size_t free = sdsavail(s);
+    void *sh, *newsh;
+    size_t avail = sdsavail(s);
     size_t len, newlen;
+    char type, oldtype = s[-1] & SDS_TYPE_MASK;
+    int hdrlen;
+
+    /* Return ASAP if there is enough space left. */
+    if (avail >= addlen) return s;
 
-    if (free >= addlen) return s;
     len = sdslen(s);
-    sh = (void*) (s-(sizeof(struct sdshdr)));
+    sh = (char*)s-sdsHdrSize(oldtype);
     newlen = (len+addlen);
     if (newlen < SDS_MAX_PREALLOC)
         newlen *= 2;
     else
         newlen += SDS_MAX_PREALLOC;
-    newsh = zrealloc(sh, sizeof(struct sdshdr)+newlen+1);
-    if (newsh == NULL) return NULL;
 
-    newsh->free = newlen - len;
-    return newsh->buf;
+    type = sdsReqType(newlen);
+
+    /* Don't use type 5: the user is appending to the string and type 5 is
+     * not able to remember empty space, so sdsMakeRoomFor() must be called
+     * at every appending operation. */
+    if (type == SDS_TYPE_5) type = SDS_TYPE_8;
+
+    hdrlen = sdsHdrSize(type);
+    if (oldtype==type) {
+        newsh = s_realloc(sh, hdrlen+newlen+1);
+        if (newsh == NULL) return NULL;
+        s = (char*)newsh+hdrlen;
+    } else {
+        /* Since the header size changes, need to move the string forward,
+         * and can't use realloc */
+        newsh = s_malloc(hdrlen+newlen+1);
+        if (newsh == NULL) return NULL;
+        memcpy((char*)newsh+hdrlen, s, len+1);
+        s_free(sh);
+        s = (char*)newsh+hdrlen;
+        s[-1] = type;
+        sdssetlen(s, len);
+    }
+    sdssetalloc(s, newlen);
+    return s;
 }
 
 /* Reallocate the sds string so that it has no free space at the end. The
  * contained string remains not altered, but next concatenation operations
  * will require a reallocation.
  *
  * After the call, the passed sds string is no longer valid and all the
  * references must be substituted with the new pointer returned by the call. */
 sds sdsRemoveFreeSpace(sds s) {
-    struct sdshdr *sh;
-
-    sh = (void*) (s-(sizeof(struct sdshdr)));
-    sh = zrealloc(sh, sizeof(struct sdshdr)+sh->len+1);
-    sh->free = 0;
-    return sh->buf;
+    void *sh, *newsh;
+    char type, oldtype = s[-1] & SDS_TYPE_MASK;
+    int hdrlen;
+    size_t len = sdslen(s);
+    sh = (char*)s-sdsHdrSize(oldtype);
+
+    type = sdsReqType(len);
+    hdrlen = sdsHdrSize(type);
+    if (oldtype==type) {
+        newsh = s_realloc(sh, hdrlen+len+1);
+        if (newsh == NULL) return NULL;
+        s = (char*)newsh+hdrlen;
+    } else {
+        newsh = s_malloc(hdrlen+len+1);
+        if (newsh == NULL) return NULL;
+        memcpy((char*)newsh+hdrlen, s, len+1);
+        s_free(sh);
+        s = (char*)newsh+hdrlen;
+        s[-1] = type;
+        sdssetlen(s, len);
+    }
+    sdssetalloc(s, len);
+    return s;
 }
 
 /* Return the total size of the allocation of the specifed sds string,
  * including:
  * 1) The sds header before the pointer.
  * 2) The string.
  * 3) The free buffer at the end if any.
  * 4) The implicit null term.
  */
 size_t sdsAllocSize(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    size_t alloc = sdsalloc(s);
+    return sdsHdrSize(s[-1])+alloc+1;
+}
 
-    return sizeof(*sh)+sh->len+sh->free+1;
+/* Return the pointer of the actual SDS allocation (normally SDS strings
+ * are referenced by the start of the string buffer). */
+void *sdsAllocPtr(sds s) {
+    return (void*) (s-sdsHdrSize(s[-1]));
 }
 
 /* Increment the sds length and decrements the left free space at the
  * end of the string according to 'incr'. Also set the null term
  * in the new end of the string.
  *
