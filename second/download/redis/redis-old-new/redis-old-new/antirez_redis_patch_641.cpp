@@ -143,6 +143,7 @@
 #define ZIPLIST_TAIL_OFFSET(zl) (*((uint32_t*)((zl)+sizeof(uint32_t))))
 #define ZIPLIST_LENGTH(zl)      (*((uint16_t*)((zl)+sizeof(uint32_t)*2)))
 #define ZIPLIST_HEADER_SIZE     (sizeof(uint32_t)*2+sizeof(uint16_t))
+#define ZIPLIST_END_SIZE        (sizeof(uint8_t))
 #define ZIPLIST_ENTRY_HEAD(zl)  ((zl)+ZIPLIST_HEADER_SIZE)
 #define ZIPLIST_ENTRY_TAIL(zl)  ((zl)+intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl)))
 #define ZIPLIST_ENTRY_END(zl)   ((zl)+intrev32ifbe(ZIPLIST_BYTES(zl))-1)
@@ -162,13 +163,22 @@ typedef struct zlentry {
     unsigned char *p;
 } zlentry;
 
+#define ZIPLIST_ENTRY_ZERO(zle) { \
+    (zle)->prevrawlensize = (zle)->prevrawlen = 0; \
+    (zle)->lensize = (zle)->len = (zle)->headersize = 0; \
+    (zle)->encoding = 0; \
+    (zle)->p = NULL; \
+}
+
 /* Extract the encoding from the byte pointed by 'ptr' and set it into
  * 'encoding'. */
 #define ZIP_ENTRY_ENCODING(ptr, encoding) do {  \
     (encoding) = (ptr[0]); \
     if ((encoding) < ZIP_STR_MASK) (encoding) &= ZIP_STR_MASK; \
 } while(0)
 
+void ziplistRepr(unsigned char *zl);
+
 /* Return bytes needed to store integer encoded by 'encoding' */
 static unsigned int zipIntSize(unsigned char encoding) {
     switch(encoding) {
@@ -404,14 +414,12 @@ static int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
 }
 
 /* Return a struct with all information about an entry. */
-static zlentry zipEntry(unsigned char *p) {
-    zlentry e;
-
-    ZIP_DECODE_PREVLEN(p, e.prevrawlensize, e.prevrawlen);
-    ZIP_DECODE_LENGTH(p + e.prevrawlensize, e.encoding, e.lensize, e.len);
-    e.headersize = e.prevrawlensize + e.lensize;
-    e.p = p;
-    return e;
+static void zipEntry(unsigned char *p, zlentry *e) {
+
+    ZIP_DECODE_PREVLEN(p, e->prevrawlensize, e->prevrawlen);
+    ZIP_DECODE_LENGTH(p + e->prevrawlensize, e->encoding, e->lensize, e->len);
+    e->headersize = e->prevrawlensize + e->lensize;
+    e->p = p;
 }
 
 /* Create a new empty ziplist. */
@@ -460,13 +468,13 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
     zlentry cur, next;
 
     while (p[0] != ZIP_END) {
-        cur = zipEntry(p);
+        zipEntry(p, &cur);
         rawlen = cur.headersize + cur.len;
         rawlensize = zipPrevEncodeLength(NULL,rawlen);
 
         /* Abort if there is no next entry. */
         if (p[rawlen] == ZIP_END) break;
-        next = zipEntry(p+rawlen);
+        zipEntry(p+rawlen, &next);
 
         /* Abort when "prevlen" has not changed. */
         if (next.prevrawlen == rawlen) break;
@@ -521,7 +529,7 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
     int nextdiff = 0;
     zlentry first, tail;
 
-    first = zipEntry(p);
+    zipEntry(p, &first);
     for (i = 0; p[0] != ZIP_END && i < num; i++) {
         p += zipRawEntryLength(p);
         deleted++;
@@ -545,7 +553,7 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
             /* When the tail contains more than one entry, we need to take
              * "nextdiff" in account as well. Otherwise, a change in the
              * size of prevlen doesn't have an effect on the *tail* offset. */
-            tail = zipEntry(p);
+            zipEntry(p, &tail);
             if (p[tail.headersize+tail.len] != ZIP_END) {
                 ZIPLIST_TAIL_OFFSET(zl) =
                    intrev32ifbe(intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))+nextdiff);
@@ -635,7 +643,7 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
         /* When the tail contains more than one entry, we need to take
          * "nextdiff" in account as well. Otherwise, a change in the
          * size of prevlen doesn't have an effect on the *tail* offset. */
-        tail = zipEntry(p+reqlen);
+        zipEntry(p+reqlen, &tail);
         if (p[reqlen+tail.headersize+tail.len] != ZIP_END) {
             ZIPLIST_TAIL_OFFSET(zl) =
                 intrev32ifbe(intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))+nextdiff);
@@ -665,6 +673,121 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
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
@@ -748,7 +871,7 @@ unsigned int ziplistGet(unsigned char *p, unsigned char **sstr, unsigned int *sl
     if (p == NULL || p[0] == ZIP_END) return 0;
     if (sstr) *sstr = NULL;
 
-    entry = zipEntry(p);
+    zipEntry(p, &entry);
     if (ZIP_IS_STR(entry.encoding)) {
         if (sstr) {
             *slen = entry.len;
@@ -783,7 +906,7 @@ unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
 }
 
 /* Delete a range of entries from the ziplist. */
-unsigned char *ziplistDeleteRange(unsigned char *zl, unsigned int index, unsigned int num) {
+unsigned char *ziplistDeleteRange(unsigned char *zl, int index, unsigned int num) {
     unsigned char *p = ziplistIndex(zl,index);
     return (p == NULL) ? zl : __ziplistDelete(zl,p,num);
 }
@@ -796,7 +919,7 @@ unsigned int ziplistCompare(unsigned char *p, unsigned char *sstr, unsigned int
     long long zval, sval;
     if (p[0] == ZIP_END) return 0;
 
-    entry = zipEntry(p);
+    zipEntry(p, &entry);
     if (ZIP_IS_STR(entry.encoding)) {
         /* Raw compare */
         if (entry.len == slen) {
@@ -913,7 +1036,7 @@ void ziplistRepr(unsigned char *zl) {
         intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl)));
     p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
-        entry = zipEntry(p);
+        zipEntry(p, &entry);
         printf(
             "{"
                 "addr 0x%08lx, "
@@ -952,14 +1075,14 @@ void ziplistRepr(unsigned char *zl) {
     printf("{end}\n\n");
 }
 
-#ifdef ZIPLIST_TEST_MAIN
+#ifdef REDIS_TEST
 #include <sys/time.h>
 #include "adlist.h"
 #include "sds.h"
 
 #define debug(f, ...) { if (DEBUG) printf(f, __VA_ARGS__); }
 
-unsigned char *createList() {
+static unsigned char *createList() {
     unsigned char *zl = ziplistNew();
     zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
     zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
@@ -968,7 +1091,7 @@ unsigned char *createList() {
     return zl;
 }
 
-unsigned char *createIntList() {
+static unsigned char *createIntList() {
     unsigned char *zl = ziplistNew();
     char buf[32];
 
@@ -987,13 +1110,13 @@ unsigned char *createIntList() {
     return zl;
 }
 
-long long usec(void) {
+static long long usec(void) {
     struct timeval tv;
     gettimeofday(&tv,NULL);
     return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
 }
 
-void stress(int pos, int num, int maxsize, int dnum) {
+static void stress(int pos, int num, int maxsize, int dnum) {
     int i,j,k;
     unsigned char *zl;
     char posstr[2][5] = { "HEAD", "TAIL" };
@@ -1016,7 +1139,7 @@ void stress(int pos, int num, int maxsize, int dnum) {
     }
 }
 
-void pop(unsigned char *zl, int where) {
+static unsigned char *pop(unsigned char *zl, int where) {
     unsigned char *p, *vstr;
     unsigned int vlen;
     long long vlong;
@@ -1028,20 +1151,22 @@ void pop(unsigned char *zl, int where) {
         else
             printf("Pop tail: ");
 
-        if (vstr)
+        if (vstr) {
             if (vlen && fwrite(vstr,vlen,1,stdout) == 0) perror("fwrite");
-        else
+        }
+        else {
             printf("%lld", vlong);
+        }
 
         printf("\n");
-        ziplistDeleteRange(zl,-1,1);
+        return ziplistDelete(zl,&p);
     } else {
         printf("ERROR: Could not pop\n");
         exit(1);
     }
 }
 
-int randstring(char *target, unsigned int min, unsigned int max) {
+static int randstring(char *target, unsigned int min, unsigned int max) {
     int p = 0;
     int len = min+rand()%(max-min+1);
     int minval, maxval;
@@ -1067,23 +1192,24 @@ int randstring(char *target, unsigned int min, unsigned int max) {
     return len;
 }
 
-void verify(unsigned char *zl, zlentry *e) {
-    int i;
+static void verify(unsigned char *zl, zlentry *e) {
     int len = ziplistLen(zl);
     zlentry _e;
 
-    for (i = 0; i < len; i++) {
+    ZIPLIST_ENTRY_ZERO(&_e);
+
+    for (int i = 0; i < len; i++) {
         memset(&e[i], 0, sizeof(zlentry));
-        e[i] = zipEntry(ziplistIndex(zl, i));
+        zipEntry(ziplistIndex(zl, i), &e[i]);
 
         memset(&_e, 0, sizeof(zlentry));
-        _e = zipEntry(ziplistIndex(zl, -len+i));
+        zipEntry(ziplistIndex(zl, -len+i), &_e);
 
         assert(memcmp(&e[i], &_e, sizeof(zlentry)) == 0);
     }
 }
 
-int main(int argc, char **argv) {
+int ziplistTest(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
     unsigned int elen;
@@ -1096,21 +1222,25 @@ int main(int argc, char **argv) {
     zl = createIntList();
     ziplistRepr(zl);
 
+    zfree(zl);
+
     zl = createList();
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_HEAD);
+    zl = pop(zl,ZIPLIST_HEAD);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
+    zfree(zl);
+
     printf("Get element at index 3:\n");
     {
         zl = createList();
@@ -1126,6 +1256,7 @@ int main(int argc, char **argv) {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index 4 (out of range):\n");
@@ -1139,6 +1270,7 @@ int main(int argc, char **argv) {
             return 1;
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index -1 (last element):\n");
@@ -1156,6 +1288,7 @@ int main(int argc, char **argv) {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index -4 (first element):\n");
@@ -1173,6 +1306,7 @@ int main(int argc, char **argv) {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index -5 (reverse out of range):\n");
@@ -1186,6 +1320,7 @@ int main(int argc, char **argv) {
             return 1;
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 0 to end:\n");
@@ -1203,6 +1338,7 @@ int main(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 1 to end:\n");
@@ -1220,6 +1356,7 @@ int main(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 2 to end:\n");
@@ -1237,6 +1374,7 @@ int main(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate starting out of range:\n");
@@ -1249,6 +1387,7 @@ int main(int argc, char **argv) {
             printf("ERROR\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate from back to front:\n");
@@ -1266,6 +1405,7 @@ int main(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate from back to front, deleting all items:\n");
@@ -1284,41 +1424,47 @@ int main(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Delete inclusive range 0,0:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 0, 1);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete inclusive range 0,1:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 0, 2);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete inclusive range 1,2:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 1, 2);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete with start index out of range:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 5, 1);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete with num overflow:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 1, 5);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete foo while iterating:\n");
@@ -1343,11 +1489,12 @@ int main(int argc, char **argv) {
         }
         printf("\n");
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Regression test for >255 byte strings:\n");
     {
-        char v1[257],v2[257];
+        char v1[257] = {0}, v2[257] = {0};
         memset(v1,'x',256);
         memset(v2,'y',256);
         zl = ziplistNew();
@@ -1362,13 +1509,15 @@ int main(int argc, char **argv) {
         assert(ziplistGet(p,&entry,&elen,&value));
         assert(strncmp(v2,(char*)entry,elen) == 0);
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Regression test deleting next to last entries:\n");
     {
-        char v[3][257];
-        zlentry e[3];
-        int i;
+        char v[3][257] = {{0}};
+        zlentry e[3] = {{.prevrawlensize = 0, .prevrawlen = 0, .lensize = 0,
+                         .len = 0, .headersize = 0, .encoding = 0, .p = NULL}};
+        size_t i;
 
         for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++) {
             memset(v[i], 'a' + i, sizeof(v[0]));
@@ -1399,6 +1548,7 @@ int main(int argc, char **argv) {
         assert(e[1].prevrawlensize == 5);
 
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Create long list and check indices:\n");
@@ -1420,6 +1570,7 @@ int main(int argc, char **argv) {
             assert(999-i == value);
         }
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Compare strings with ziplist entries:\n");
@@ -1445,6 +1596,82 @@ int main(int argc, char **argv) {
             return 1;
         }
         printf("SUCCESS\n\n");
+        zfree(zl);
+    }
+
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
+        zfree(zl);
     }
 
     printf("Stress with random payloads of different encoding:\n");
@@ -1464,7 +1691,7 @@ int main(int argc, char **argv) {
         for (i = 0; i < 20000; i++) {
             zl = ziplistNew();
             ref = listCreate();
-            listSetFreeMethod(ref,sdsfree);
+            listSetFreeMethod(ref,(void (*)(void*))sdsfree);
             len = rand() % 256;
 
             /* Create lists */
@@ -1532,5 +1759,4 @@ int main(int argc, char **argv) {
 
     return 0;
 }
-
 #endif