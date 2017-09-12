@@ -1,17 +1,63 @@
-/* Memory layout of a ziplist, containing "foo", "bar", "quux":
- * <zlbytes><zllen><len>"foo"<len>"bar"<len>"quux"
+/* The ziplist is a specially encoded dually linked list that is designed
+ * to be very memory efficient. It stores both strings and integer values,
+ * where integers are encoded as actual integers instead of a series of
+ * characters. It allows push and pop operations on either side of the list
+ * in O(1) time. However, because every operation requires a reallocation of
+ * the memory used by the ziplist, the actual complexity is related to the
+ * amount of memory used by the ziplist.
  *
- * <zlbytes> is an unsigned integer to hold the number of bytes that
- * the ziplist occupies. This is stored to not have to traverse the ziplist
- * to know the new length when pushing.
+ * ----------------------------------------------------------------------------
  *
- * <zllen> is the number of items in the ziplist. When this value is
- * greater than 254, we need to traverse the entire list to know
- * how many items it holds.
+ * ZIPLIST OVERALL LAYOUT:
+ * The general layout of the ziplist is as follows:
+ * <zlbytes><zltail><zllen><entry><entry><zlend>
  *
- * <len> is the number of bytes occupied by a single entry. When this
- * number is greater than 253, the length will occupy 5 bytes, where
- * the extra bytes contain an unsigned integer to hold the length.
+ * <zlbytes> is an unsigned integer to hold the number of bytes that the
+ * ziplist occupies. This value needs to be stored to be able to resize the
+ * entire structure without the need to traverse it first.
+ *
+ * <zltail> is the offset to the last entry in the list. This allows a pop
+ * operation on the far side of the list without the need for full traversal.
+ *
+ * <zllen> is the number of entries.When this value is larger than 2**16-2,
+ * we need to traverse the entire list to know how many items it holds.
+ *
+ * <zlend> is a single byte special value, equal to 255, which indicates the
+ * end of the list.
+ *
+ * ZIPLIST ENTRIES:
+ * Every entry in the ziplist is prefixed by a header that contains two pieces
+ * of information. First, the length of the previous entry is stored to be
+ * able to traverse the list from back to front. Second, the encoding with an
+ * optional string length of the entry itself is stored.
+ *
+ * The length of the previous entry is encoded in the following way:
+ * If this length is smaller than 254 bytes, it will only consume a single
+ * byte that takes the length as value. When the length is greater than or
+ * equal to 254, it will consume 5 bytes. The first byte is set to 254 to
+ * indicate a larger value is following. The remaining 4 bytes take the
+ * length of the previous entry as value.
+ *
+ * The other header field of the entry itself depends on the contents of the
+ * entry. When the entry is a string, the first 2 bits of this header will hold
+ * the type of encoding used to store the length of the string, followed by the
+ * actual length of the string. When the entry is an integer the first 2 bits
+ * are both set to 1. The following 2 bits are used to specify what kind of
+ * integer will be stored after this header. An overview of the different
+ * types and encodings is as follows:
+ *
+ * |00pppppp| - 1 byte
+ *      String value with length less than or equal to 63 bytes (6 bits).
+ * |01pppppp|qqqqqqqq| - 2 bytes
+ *      String value with length less than or equal to 16383 bytes (14 bits).
+ * |10______|qqqqqqqq|rrrrrrrr|ssssssss|tttttttt| - 5 bytes
+ *      String value with length greater than or equal to 16384 bytes.
+ * |1100____| - 1 byte
+ *      Integer encoded as int16_t (2 bytes).
+ * |1101____| - 1 byte
+ *      Integer encoded as int32_t (4 bytes).
+ * |1110____| - 1 byte
+ *      Integer encoded as int64_t (8 bytes).
  */
 
 #include <stdio.h>
@@ -25,25 +71,20 @@
 
 int ll2string(char *s, size_t len, long long value);
 
-/* Important note: the ZIP_END value is used to depict the end of the
- * ziplist structure. When a pointer contains an entry, the first couple
- * of bytes contain the encoded length of the previous entry. This length
- * is encoded as ZIP_ENC_RAW length, so the first two bits will contain 00
- * and the byte will therefore never have a value of 255. */
 #define ZIP_END 255
 #define ZIP_BIGLEN 254
 
-/* Entry encoding */
-#define ZIP_ENC_RAW     0
-#define ZIP_ENC_INT16   1
-#define ZIP_ENC_INT32   2
-#define ZIP_ENC_INT64   3
-#define ZIP_ENCODING(p) ((p)[0] >> 6)
+/* Different encoding/length possibilities */
+#define ZIP_STR_06B (0 << 6)
+#define ZIP_STR_14B (1 << 6)
+#define ZIP_STR_32B (2 << 6)
+#define ZIP_INT_16B (0xc0 | 0<<4)
+#define ZIP_INT_32B (0xc0 | 1<<4)
+#define ZIP_INT_64B (0xc0 | 2<<4)
 
-/* Length encoding for raw entries */
-#define ZIP_LEN_INLINE  0
-#define ZIP_LEN_UINT16  1
-#define ZIP_LEN_UINT32  2
+/* Macro's to determine type */
+#define ZIP_IS_STR(enc) (((enc) & 0xc0) < 0xc0)
+#define ZIP_IS_INT(enc) (!ZIP_IS_STR(enc) && ((enc) & 0x30) < 0x30)
 
 /* Utility macros */
 #define ZIPLIST_BYTES(zl)       (*((uint32_t*)(zl)))
@@ -67,73 +108,91 @@ typedef struct zlentry {
     unsigned char *p;
 } zlentry;
 
+/* Return the encoding pointer to by 'p'. */
+static unsigned int zipEntryEncoding(unsigned char *p) {
+    /* String encoding: 2 MSBs */
+    unsigned char b = p[0] & 0xc0;
+    if (b < 0xc0) {
+        return b;
+    } else {
+        /* Integer encoding: 4 MSBs */
+        return p[0] & 0xf0;
+    }
+    assert(NULL);
+}
+
 /* Return bytes needed to store integer encoded by 'encoding' */
-static unsigned int zipEncodingSize(unsigned char encoding) {
-    if (encoding == ZIP_ENC_INT16) {
-        return sizeof(int16_t);
-    } else if (encoding == ZIP_ENC_INT32) {
-        return sizeof(int32_t);
-    } else if (encoding == ZIP_ENC_INT64) {
-        return sizeof(int64_t);
+static unsigned int zipIntSize(unsigned char encoding) {
+    switch(encoding) {
+    case ZIP_INT_16B: return sizeof(int16_t);
+    case ZIP_INT_32B: return sizeof(int32_t);
+    case ZIP_INT_64B: return sizeof(int64_t);
     }
     assert(NULL);
 }
 
 /* Decode the encoded length pointed by 'p'. If a pointer to 'lensize' is
  * provided, it is set to the number of bytes required to encode the length. */
 static unsigned int zipDecodeLength(unsigned char *p, unsigned int *lensize) {
-    unsigned char encoding = ZIP_ENCODING(p), lenenc;
+    unsigned char encoding = zipEntryEncoding(p);
     unsigned int len;
 
-    if (encoding == ZIP_ENC_RAW) {
-        lenenc = (p[0] >> 4) & 0x3;
-        if (lenenc == ZIP_LEN_INLINE) {
-            len = p[0] & 0xf;
+    if (ZIP_IS_STR(encoding)) {
+        switch(encoding) {
+        case ZIP_STR_06B:
+            len = p[0] & 0x3f;
             if (lensize) *lensize = 1;
-        } else if (lenenc == ZIP_LEN_UINT16) {
-            len = p[1] | (p[2] << 8);
-            if (lensize) *lensize = 3;
-        } else {
-            len = p[1] | (p[2] << 8) | (p[3] << 16) | (p[4] << 24);
+            break;
+        case ZIP_STR_14B:
+            len = ((p[0] & 0x3f) << 8) | p[1];
+            if (lensize) *lensize = 2;
+            break;
+        case ZIP_STR_32B:
+            len = (p[1] << 24) | (p[2] << 16) | (p[3] << 8) | p[4];
             if (lensize) *lensize = 5;
+            break;
+        default:
+            assert(NULL);
         }
     } else {
-        len = zipEncodingSize(encoding);
+        len = zipIntSize(encoding);
         if (lensize) *lensize = 1;
     }
     return len;
 }
 
 /* Encode the length 'l' writing it in 'p'. If p is NULL it just returns
  * the amount of bytes required to encode such a length. */
-static unsigned int zipEncodeLength(unsigned char *p, char encoding, unsigned int rawlen) {
-    unsigned char len = 1, lenenc, buf[5];
-    if (encoding == ZIP_ENC_RAW) {
-        if (rawlen <= 0xf) {
+static unsigned int zipEncodeLength(unsigned char *p, unsigned char encoding, unsigned int rawlen) {
+    unsigned char len = 1, buf[5];
+
+    if (ZIP_IS_STR(encoding)) {
+        /* Although encoding is given it may not be set for strings,
+         * so we determine it here using the raw length. */
+        if (rawlen <= 0x3f) {
             if (!p) return len;
-            lenenc = ZIP_LEN_INLINE;
-            buf[0] = rawlen;
-        } else if (rawlen <= 0xffff) {
-            len += 2;
+            buf[0] = ZIP_STR_06B | rawlen;
+        } else if (rawlen <= 0x3fff) {
+            len += 1;
             if (!p) return len;
-            lenenc = ZIP_LEN_UINT16;
-            buf[1] = (rawlen     ) & 0xff;
-            buf[2] = (rawlen >> 8) & 0xff;
+            buf[0] = ZIP_STR_14B | ((rawlen >> 8) & 0x3f);
+            buf[1] = rawlen & 0xff;
         } else {
             len += 4;
             if (!p) return len;
-            lenenc = ZIP_LEN_UINT32;
-            buf[1] = (rawlen      ) & 0xff;
-            buf[2] = (rawlen >>  8) & 0xff;
-            buf[3] = (rawlen >> 16) & 0xff;
-            buf[4] = (rawlen >> 24) & 0xff;
+            buf[0] = ZIP_STR_32B;
+            buf[1] = (rawlen >> 24) & 0xff;
+            buf[2] = (rawlen >> 16) & 0xff;
+            buf[3] = (rawlen >> 8) & 0xff;
+            buf[4] = rawlen & 0xff;
         }
-        buf[0] = (lenenc << 4) | (buf[0] & 0xf);
+    } else {
+        /* Implies integer encoding, so length is always 1. */
+        if (!p) return len;
+        buf[0] = encoding;
     }
-    if (!p) return len;
 
-    /* Apparently we need to store the length in 'p' */
-    buf[0] = (encoding << 6) | (buf[0] & 0x3f);
+    /* Store this length at p */
     memcpy(p,buf,len);
     return len;
 }
@@ -167,6 +226,14 @@ static unsigned int zipPrevEncodeLength(unsigned char *p, unsigned int len) {
     }
 }
 
+/* Encode the length of the previous entry and write it to "p". This only
+ * uses the larger encoding (required in __ziplistCascadeUpdate). */
+static void zipPrevEncodeLengthForceLarge(unsigned char *p, unsigned int len) {
+    if (p == NULL) return;
+    p[0] = ZIP_BIGLEN;
+    memcpy(p+1,&len,sizeof(len));
+}
+
 /* Return the difference in number of bytes needed to store the new length
  * "len" on the entry pointed to by "p". */
 static int zipPrevLenByteDiff(unsigned char *p, unsigned int len) {
@@ -198,11 +265,11 @@ static int zipTryEncoding(unsigned char *entry, unsigned int entrylen, long long
         /* Great, the string can be encoded. Check what's the smallest
          * of our encoding types that can hold this value. */
         if (value >= INT16_MIN && value <= INT16_MAX) {
-            *encoding = ZIP_ENC_INT16;
+            *encoding = ZIP_INT_16B;
         } else if (value >= INT32_MIN && value <= INT32_MAX) {
-            *encoding = ZIP_ENC_INT32;
+            *encoding = ZIP_INT_32B;
         } else {
-            *encoding = ZIP_ENC_INT64;
+            *encoding = ZIP_INT_64B;
         }
         *v = value;
         return 1;
@@ -215,13 +282,13 @@ static void zipSaveInteger(unsigned char *p, int64_t value, unsigned char encodi
     int16_t i16;
     int32_t i32;
     int64_t i64;
-    if (encoding == ZIP_ENC_INT16) {
+    if (encoding == ZIP_INT_16B) {
         i16 = value;
         memcpy(p,&i16,sizeof(i16));
-    } else if (encoding == ZIP_ENC_INT32) {
+    } else if (encoding == ZIP_INT_32B) {
         i32 = value;
         memcpy(p,&i32,sizeof(i32));
-    } else if (encoding == ZIP_ENC_INT64) {
+    } else if (encoding == ZIP_INT_64B) {
         i64 = value;
         memcpy(p,&i64,sizeof(i64));
     } else {
@@ -234,13 +301,13 @@ static int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
     int16_t i16;
     int32_t i32;
     int64_t i64, ret;
-    if (encoding == ZIP_ENC_INT16) {
+    if (encoding == ZIP_INT_16B) {
         memcpy(&i16,p,sizeof(i16));
         ret = i16;
-    } else if (encoding == ZIP_ENC_INT32) {
+    } else if (encoding == ZIP_INT_32B) {
         memcpy(&i32,p,sizeof(i32));
         ret = i32;
-    } else if (encoding == ZIP_ENC_INT64) {
+    } else if (encoding == ZIP_INT_64B) {
         memcpy(&i64,p,sizeof(i64));
         ret = i64;
     } else {
@@ -255,7 +322,7 @@ static zlentry zipEntry(unsigned char *p) {
     e.prevrawlen = zipPrevDecodeLength(p,&e.prevrawlensize);
     e.len = zipDecodeLength(p+e.prevrawlensize,&e.lensize);
     e.headersize = e.prevrawlensize+e.lensize;
-    e.encoding = ZIP_ENCODING(p+e.prevrawlensize);
+    e.encoding = zipEntryEncoding(p+e.prevrawlensize);
     e.p = p;
     return e;
 }
@@ -285,11 +352,86 @@ static unsigned char *ziplistResize(unsigned char *zl, unsigned int len) {
     return zl;
 }
 
+/* When an entry is inserted, we need to set the prevlen field of the next
+ * entry to equal the length of the inserted entry. It can occur that this
+ * length cannot be encoded in 1 byte and the next entry needs to be grow
+ * a bit larger to hold the 5-byte encoded prevlen. This can be done for free,
+ * because this only happens when an entry is already being inserted (which
+ * causes a realloc and memmove). However, encoding the prevlen may require
+ * that this entry is grown as well. This effect may cascade throughout
+ * the ziplist when there are consecutive entries with a size close to
+ * ZIP_BIGLEN, so we need to check that the prevlen can be encoded in every
+ * consecutive entry.
+ *
+ * Note that this effect can also happen in reverse, where the bytes required
+ * to encode the prevlen field can shrink. This effect is deliberately ignored,
+ * because it can cause a "flapping" effect where a chain prevlen fields is
+ * first grown and then shrunk again after consecutive inserts. Rather, the
+ * field is allowed to stay larger than necessary, because a large prevlen
+ * field implies the ziplist is holding large entries anyway.
+ *
+ * The pointer "p" points to the first entry that does NOT need to be
+ * updated, i.e. consecutive fields MAY need an update. */
+static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p) {
+    unsigned int curlen = ZIPLIST_BYTES(zl), rawlen, rawlensize;
+    unsigned int offset, noffset, extra;
+    unsigned char *np;
+    zlentry cur, next;
+
+    while (p[0] != ZIP_END) {
+        cur = zipEntry(p);
+        rawlen = cur.headersize + cur.len;
+        rawlensize = zipPrevEncodeLength(NULL,rawlen);
+
+        /* Abort if there is no next entry. */
+        if (p[rawlen] == ZIP_END) break;
+        next = zipEntry(p+rawlen);
+
+        /* Abort when "prevlen" has not changed. */
+        if (next.prevrawlen == rawlen) break;
+
+        if (next.prevrawlensize < rawlensize) {
+            /* The "prevlen" field of "next" needs more bytes to hold
+             * the raw length of "cur". */
+            offset = p-zl;
+            extra = rawlensize-next.prevrawlensize;
+            zl = ziplistResize(zl,curlen+extra);
+            ZIPLIST_TAIL_OFFSET(zl) += extra;
+            p = zl+offset;
+
+            /* Move the tail to the back. */
+            np = p+rawlen;
+            noffset = np-zl;
+            memmove(np+rawlensize,
+                np+next.prevrawlensize,
+                curlen-noffset-next.prevrawlensize-1);
+            zipPrevEncodeLength(np,rawlen);
+
+            /* Advance the cursor */
+            p += rawlen;
+        } else {
+            if (next.prevrawlensize > rawlensize) {
+                /* This would result in shrinking, which we want to avoid.
+                 * So, set "rawlen" in the available bytes. */
+                zipPrevEncodeLengthForceLarge(p+rawlen,rawlen);
+            } else {
+                zipPrevEncodeLength(p+rawlen,rawlen);
+            }
+
+            /* Stop here, as the raw length of "next" has not changed. */
+            break;
+        }
+    }
+    return zl;
+}
+
 /* Delete "num" entries, starting at "p". Returns pointer to the ziplist. */
 static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsigned int num) {
     unsigned int i, totlen, deleted = 0;
-    int nextdiff = 0;
-    zlentry first = zipEntry(p);
+    int offset, nextdiff = 0;
+    zlentry first, tail;
+
+    first = zipEntry(p);
     for (i = 0; p[0] != ZIP_END && i < num; i++) {
         p += zipRawEntryLength(p);
         deleted++;
@@ -306,7 +448,14 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
             zipPrevEncodeLength(p-nextdiff,first.prevrawlen);
 
             /* Update offset for tail */
-            ZIPLIST_TAIL_OFFSET(zl) -= totlen+nextdiff;
+            ZIPLIST_TAIL_OFFSET(zl) -= totlen;
+
+            /* When the tail contains more than one entry, we need to take
+             * "nextdiff" in account as well. Otherwise, a change in the
+             * size of prevlen doesn't have an effect on the *tail* offset. */
+            tail = zipEntry(p);
+            if (p[tail.headersize+tail.len] != ZIP_END)
+                ZIPLIST_TAIL_OFFSET(zl) += nextdiff;
 
             /* Move tail to the front of the ziplist */
             memmove(first.p,p-nextdiff,ZIPLIST_BYTES(zl)-(p-zl)-1+nextdiff);
@@ -316,8 +465,15 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
         }
 
         /* Resize and update length */
+        offset = first.p-zl;
         zl = ziplistResize(zl, ZIPLIST_BYTES(zl)-totlen+nextdiff);
         ZIPLIST_INCR_LENGTH(zl,-deleted);
+        p = zl+offset;
+
+        /* When nextdiff != 0, the raw length of the next entry has changed, so
+         * we need to cascade the update throughout the ziplist */
+        if (nextdiff != 0)
+            zl = __ziplistCascadeUpdate(zl,p);
     }
     return zl;
 }
@@ -326,29 +482,30 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
 static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
     unsigned int curlen = ZIPLIST_BYTES(zl), reqlen, prevlen = 0;
     unsigned int offset, nextdiff = 0;
-    unsigned char *tail;
-    unsigned char encoding = ZIP_ENC_RAW;
+    unsigned char encoding = 0;
     long long value;
-    zlentry entry;
+    zlentry entry, tail;
 
     /* Find out prevlen for the entry that is inserted. */
     if (p[0] != ZIP_END) {
         entry = zipEntry(p);
         prevlen = entry.prevrawlen;
     } else {
-        tail = ZIPLIST_ENTRY_TAIL(zl);
-        if (tail[0] != ZIP_END) {
-            prevlen = zipRawEntryLength(tail);
+        unsigned char *ptail = ZIPLIST_ENTRY_TAIL(zl);
+        if (ptail[0] != ZIP_END) {
+            prevlen = zipRawEntryLength(ptail);
         }
     }
 
     /* See if the entry can be encoded */
     if (zipTryEncoding(s,slen,&value,&encoding)) {
-        reqlen = zipEncodingSize(encoding);
+        /* 'encoding' is set to the appropriate integer encoding */
+        reqlen = zipIntSize(encoding);
     } else {
+        /* 'encoding' is untouched, however zipEncodeLength will use the
+         * string length to figure out how to encode it. */
         reqlen = slen;
     }
-
     /* We need space for both the length of the previous entry and
      * the length of the payload. */
     reqlen += zipPrevEncodeLength(NULL,prevlen);
@@ -368,22 +525,39 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
     if (p[0] != ZIP_END) {
         /* Subtract one because of the ZIP_END bytes */
         memmove(p+reqlen,p-nextdiff,curlen-offset-1+nextdiff);
+
         /* Encode this entry's raw length in the next entry. */
         zipPrevEncodeLength(p+reqlen,reqlen);
+
         /* Update offset for tail */
-        ZIPLIST_TAIL_OFFSET(zl) += reqlen+nextdiff;
+        ZIPLIST_TAIL_OFFSET(zl) += reqlen;
+
+        /* When the tail contains more than one entry, we need to take
+         * "nextdiff" in account as well. Otherwise, a change in the
+         * size of prevlen doesn't have an effect on the *tail* offset. */
+        tail = zipEntry(p+reqlen);
+        if (p[reqlen+tail.headersize+tail.len] != ZIP_END)
+            ZIPLIST_TAIL_OFFSET(zl) += nextdiff;
     } else {
         /* This element will be the new tail. */
         ZIPLIST_TAIL_OFFSET(zl) = p-zl;
     }
 
+    /* When nextdiff != 0, the raw length of the next entry has changed, so
+     * we need to cascade the update throughout the ziplist */
+    if (nextdiff != 0) {
+        offset = p-zl;
+        zl = __ziplistCascadeUpdate(zl,p+reqlen);
+        p = zl+offset;
+    }
+
     /* Write the entry */
     p += zipPrevEncodeLength(p,prevlen);
     p += zipEncodeLength(p,encoding,slen);
-    if (encoding != ZIP_ENC_RAW) {
-        zipSaveInteger(p,value,encoding);
-    } else {
+    if (ZIP_IS_STR(encoding)) {
         memcpy(p,s,slen);
+    } else {
+        zipSaveInteger(p,value,encoding);
     }
     ZIPLIST_INCR_LENGTH(zl,1);
     return zl;
@@ -449,6 +623,7 @@ unsigned char *ziplistPrev(unsigned char *zl, unsigned char *p) {
         return NULL;
     } else {
         entry = zipEntry(p);
+        assert(entry.prevrawlen > 0);
         return p-entry.prevrawlen;
     }
 }
@@ -463,7 +638,7 @@ unsigned int ziplistGet(unsigned char *p, unsigned char **sstr, unsigned int *sl
     if (sstr) *sstr = NULL;
 
     entry = zipEntry(p);
-    if (entry.encoding == ZIP_ENC_RAW) {
+    if (ZIP_IS_STR(entry.encoding)) {
         if (sstr) {
             *slen = entry.len;
             *sstr = p+entry.headersize;
@@ -510,7 +685,7 @@ unsigned int ziplistCompare(unsigned char *p, unsigned char *sstr, unsigned int
     if (p[0] == ZIP_END) return 0;
 
     entry = zipEntry(p);
-    if (entry.encoding == ZIP_ENC_RAW) {
+    if (ZIP_IS_STR(entry.encoding)) {
         /* Raw compare */
         if (entry.len == slen) {
             return memcmp(p+entry.headersize,sstr,slen) == 0;
@@ -554,21 +729,52 @@ unsigned int ziplistSize(unsigned char *zl) {
 
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p;
+    int index = 0;
     zlentry entry;
 
-    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
+    printf(
+        "{total bytes %d} "
+        "{length %u}\n"
+        "{tail offset %u}\n",
+        ZIPLIST_BYTES(zl),
+        ZIPLIST_LENGTH(zl),
+        ZIPLIST_TAIL_OFFSET(zl));
     p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
         entry = zipEntry(p);
-        printf("{offset %ld, header %u, payload %u} ",p-zl,entry.headersize,entry.len);
+        printf(
+            "{"
+                "addr 0x%08lx, "
+                "index %2d, "
+                "offset %5ld, "
+                "rl: %5u, "
+                "hs %2u, "
+                "pl: %5u, "
+                "pls: %2u, "
+                "payload %5u"
+            "} ",
+            (long unsigned int)p,
+            index,
+            p-zl,
+            entry.headersize+entry.len,
+            entry.headersize,
+            entry.prevrawlen,
+            entry.prevrawlensize,
+            entry.len);
         p += entry.headersize;
-        if (entry.encoding == ZIP_ENC_RAW) {
-            fwrite(p,entry.len,1,stdout);
+        if (ZIP_IS_STR(entry.encoding)) {
+            if (entry.len > 40) {
+                fwrite(p,40,1,stdout);
+                printf("...");
+            } else {
+                fwrite(p,entry.len,1,stdout);
+            }
         } else {
             printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
         }
         printf("\n");
         p += entry.len;
+        index++;
     }
     printf("{end}\n\n");
 }
@@ -664,6 +870,10 @@ int main(int argc, char **argv) {
     unsigned int elen;
     long long value;
 
+    /* If an argument is given, use it as the random seed. */
+    if (argc == 2)
+        srand(atoi(argv[1]));
+
     zl = createIntList();
     ziplistRepr(zl);
 
@@ -915,6 +1125,25 @@ int main(int argc, char **argv) {
         ziplistRepr(zl);
     }
 
+    printf("Regression test for >255 byte strings:\n");
+    {
+        char v1[257],v2[257];
+        memset(v1,'x',256);
+        memset(v2,'y',256);
+        zl = ziplistNew();
+        zl = ziplistPush(zl,(unsigned char*)v1,strlen(v1),ZIPLIST_TAIL);
+        zl = ziplistPush(zl,(unsigned char*)v2,strlen(v2),ZIPLIST_TAIL);
+
+        /* Pop values again and compare their value. */
+        p = ziplistIndex(zl,0);
+        assert(ziplistGet(p,&entry,&elen,&value));
+        assert(strncmp(v1,entry,elen) == 0);
+        p = ziplistIndex(zl,1);
+        assert(ziplistGet(p,&entry,&elen,&value));
+        assert(strncmp(v2,entry,elen) == 0);
+        printf("SUCCESS\n\n");
+    }
+
     printf("Create long list and check indices:\n");
     {
         zl = ziplistNew();
@@ -958,7 +1187,57 @@ int main(int argc, char **argv) {
             printf("ERROR: \"1025\"\n");
             return 1;
         }
-        printf("SUCCESS\n");
+        printf("SUCCESS\n\n");
+    }
+
+    printf("Stress with random payloads of different encoding:\n");
+    {
+        int i, idx, where, len;
+        long long v;
+        unsigned char *p;
+        char buf[0x4041]; /* max length of generated string */
+        zl = ziplistNew();
+        for (i = 0; i < 100000; i++) {
+            where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
+            if (rand() & 1) {
+                /* equally likely create a 16, 32 or 64 bit int */
+                v = (rand() & INT16_MAX) + ((1ll << 32) >> ((rand() % 3)*16));
+                v *= 2*(rand() & 1)-1; /* randomly flip sign */
+                sprintf(buf, "%lld", v);
+                zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);
+            } else {
+                /* equally likely generate 6, 14 or >14 bit length */
+                v = rand() & 0x3f;
+                v += 0x4000 >> ((rand() % 3)*8);
+                memset(buf, 'x', v);
+                zl = ziplistPush(zl, (unsigned char*)buf, v, where);
+            }
+
+            /* delete a random element */
+            if ((len = ziplistLen(zl)) >= 10) {
+                idx = rand() % len;
+                // printf("Delete index %d\n", idx);
+                // ziplistRepr(zl);
+                ziplistDeleteRange(zl, idx, 1);
+                // ziplistRepr(zl);
+                len--;
+            }
+
+            /* iterate from front to back */
+            idx = 0;
+            p = ziplistIndex(zl, 0);
+            while((p = ziplistNext(zl,p)))
+                idx++;
+            assert(len == idx+1);
+
+            /* iterate from back to front */
+            idx = 0;
+            p = ziplistIndex(zl, -1);
+            while((p = ziplistPrev(zl,p)))
+                idx++;
+            assert(len == idx+1);
+        }
+        printf("SUCCESS\n\n");
     }
 
     printf("Stress with variable ziplist size:\n");