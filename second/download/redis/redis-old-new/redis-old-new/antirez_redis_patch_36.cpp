@@ -33,8 +33,14 @@
 #include <assert.h>
 #include <stdio.h>
 #include <errno.h>
+#include <math.h>
 #include "rax.h"
-#include "rax_malloc.h"
+
+#ifndef RAX_MALLOC_INCLUDE
+#define RAX_MALLOC_INCLUDE "rax_malloc.h"
+#endif
+
+#include RAX_MALLOC_INCLUDE
 
 /* This is a special pointer that is guaranteed to never have the same value
  * of a radix tree node. It's used in order to report "not found" error without
@@ -84,13 +90,15 @@ static inline int raxStackPush(raxStack *ts, void *ptr) {
             if (ts->stack == NULL) {
                 ts->stack = ts->static_items;
                 ts->oom = 1;
+                errno = ENOMEM;
                 return 0;
             }
             memcpy(ts->stack,ts->static_items,sizeof(void*)*ts->maxitems);
         } else {
             void **newalloc = rax_realloc(ts->stack,sizeof(void*)*ts->maxitems*2);
             if (newalloc == NULL) {
                 ts->oom = 1;
+                errno = ENOMEM;
                 return 0;
             }
             ts->stack = newalloc;
@@ -205,7 +213,7 @@ void *raxGetData(raxNode *n) {
  * On success the new parent node pointer is returned (it may change because
  * of the realloc, so the caller should discard 'n' and use the new value).
  * On out of memory NULL is returned, and the old node is still valid. */
-raxNode *raxAddChild(raxNode *n, char c, raxNode **childptr, raxNode ***parentlink) {
+raxNode *raxAddChild(raxNode *n, unsigned char c, raxNode **childptr, raxNode ***parentlink) {
     assert(n->iscompr == 0);
 
     size_t curlen = sizeof(raxNode)+
@@ -330,7 +338,7 @@ raxNode *raxCompressNode(raxNode *n, unsigned char *s, size_t len, raxNode **chi
     memcpy(n->data,s,len);
     if (n->iskey) raxSetData(n,data);
     raxNode **childfield = raxNodeLastChildPtr(n);
-    memcpy(childfield,&child,sizeof(child));
+    memcpy(childfield,child,sizeof(*child));
     return n;
 }
 
@@ -399,7 +407,7 @@ static inline size_t raxLowWalk(rax *rax, unsigned char *s, size_t len, raxNode
  * data is updated, and 0 is returned, otherwise the element is inserted
  * and 1 is returned. On out of memory the function returns 0 as well but
  * sets errno to ENOMEM, otherwise errno will be set to 0. */
-int raxInsert(rax *rax, unsigned char *s, size_t len, void *data) {
+int raxInsert(rax *rax, unsigned char *s, size_t len, void *data, void **old) {
     size_t i;
     int j = 0; /* Split position. If raxLowWalk() stops in a compressed
                   node, the index 'j' represents the char we stopped within the
@@ -417,6 +425,7 @@ int raxInsert(rax *rax, unsigned char *s, size_t len, void *data) {
      * data pointer. */
     if (i == len && (!h->iscompr || j == 0 /* not in the middle if j is 0 */)) {
         if (h->iskey) {
+            if (old) *old = raxGetData(h);
             raxSetData(h,data);
             errno = 0;
             return 0; /* Element already exists. */
@@ -720,6 +729,7 @@ int raxInsert(rax *rax, unsigned char *s, size_t len, void *data) {
         /* Finish! We don't need to contine with the insertion
          * algorithm for ALGO 2. The key is already inserted. */
         rax->numele++;
+        rax_free(h);
         return 1; /* Key inserted. */
     }
 
@@ -729,7 +739,6 @@ int raxInsert(rax *rax, unsigned char *s, size_t len, void *data) {
      * since i == len. */
     while(i < len) {
         raxNode *child;
-        rax->numnodes++;
 
         /* If this node is going to have a single child, and there
          * are other characters, so that that would result in a chain
@@ -755,6 +764,7 @@ int raxInsert(rax *rax, unsigned char *s, size_t len, void *data) {
             parentlink = new_parentlink;
             i++;
         }
+        rax->numnodes++;
         h = child;
     }
     raxNode *newh = raxReallocForData(h,data);
@@ -767,10 +777,16 @@ int raxInsert(rax *rax, unsigned char *s, size_t len, void *data) {
 
 oom:
     /* This code path handles out of memory after part of the sub-tree was
-     * already added. Set the node as a key, and then remove it. */
-    h->isnull = 1;
-    h->iskey = 1;
-    raxRemove(rax,s,i);
+     * already modified. Set the node as a key, and then remove it. However we
+     * do that only if the node is a terminal node, otherwise if the OOM
+     * happened reallocating a node in the middle, we don't need to free
+     * anything. */
+    if (h->size == 0) {
+        h->isnull = 1;
+        h->iskey = 1;
+        rax->numele++; /* Compensate the next remove. */
+        assert(raxRemove(rax,s,i,NULL) != 0);
+    }
     errno = ENOMEM;
     return 0;
 }
@@ -830,7 +846,7 @@ raxNode *raxRemoveChild(raxNode *parent, raxNode *child) {
      *
      * 1. To start we seek the first element in both the children
      *    pointers and edge bytes in the node. */
-    raxNode **cp = raxNodeLastChildPtr(parent) - (parent->size-1);
+    raxNode **cp = raxNodeFirstChildPtr(parent);
     raxNode **c = cp;
     unsigned char *e = parent->data;
 
@@ -855,34 +871,37 @@ raxNode *raxRemoveChild(raxNode *parent, raxNode *child) {
     memmove(((char*)cp)-1,cp,(parent->size-taillen-1)*sizeof(raxNode**));
 
     /* Move the remaining "tail" pointer at the right position as well. */
-    memmove(((char*)c)-1,c+1,taillen*sizeof(raxNode**));
+    memmove(((char*)c)-1,c+1,taillen*sizeof(raxNode**)+parent->iskey*sizeof(void*));
 
     /* 4. Update size. */
     parent->size--;
 
     /* realloc the node according to the theoretical memory usage, to free
      * data if we are over-allocating right now. */
     raxNode *newnode = rax_realloc(parent,raxNodeCurrentLength(parent));
-    debugnode("raxRemoveChild after", newnode);
+    if (newnode) {
+        debugnode("raxRemoveChild after", newnode);
+    }
     /* Note: if rax_realloc() fails we just return the old address, which
      * is valid. */
     return newnode ? newnode : parent;
 }
 
 /* Remove the specified item. Returns 1 if the item was found and
  * deleted, 0 otherwise. */
-int raxRemove(rax *rax, unsigned char *s, size_t len) {
+int raxRemove(rax *rax, unsigned char *s, size_t len, void **old) {
     raxNode *h;
     raxStack ts;
 
     debugf("### Delete: %.*s\n", (int)len, s);
     raxStackInit(&ts);
     int splitpos = 0;
-    size_t i = raxLowWalk(rax,s,len,&h,NULL,NULL,&ts);
+    size_t i = raxLowWalk(rax,s,len,&h,NULL,&splitpos,&ts);
     if (i != len || (h->iscompr && splitpos != 0) || !h->iskey) {
         raxStackFree(&ts);
         return 0;
     }
+    if (old) *old = raxGetData(h);
     h->iskey = 0;
     rax->numele--;
 
@@ -1009,6 +1028,9 @@ int raxRemove(rax *rax, unsigned char *s, size_t len) {
             raxNode **cp = raxNodeLastChildPtr(h);
             memcpy(&h,cp,sizeof(h));
             if (h->iskey || (!h->iscompr && h->size != 1)) break;
+            /* Stop here if going to the next node would result into
+             * a compressed node larger than h->size can hold. */
+            if (comprsize + h->size > RAX_NODE_MAX_SIZE) break;
             nodes++;
             comprsize += h->size;
         }
@@ -1115,6 +1137,7 @@ int raxIteratorAddChars(raxIterator *it, unsigned char *s, size_t len) {
         it->key = rax_realloc(old,new_max);
         if (it->key == NULL) {
             it->key = (!old) ? it->key_static_string : old;
+            errno = ENOMEM;
             return 0;
         }
         if (old == NULL) memcpy(it->key,it->key_static_string,it->key_len);
@@ -1190,6 +1213,8 @@ int raxIteratorNextStep(raxIterator *it, int noup) {
              * children representing keys lexicographically greater than the
              * current key. */
             while(1) {
+                int old_noup = noup;
+
                 /* Already on head? Can't go up, iteration finished. */
                 if (!noup && it->node == it->rt->head) {
                     it->flags |= RAX_ITER_EOF;
@@ -1211,9 +1236,9 @@ int raxIteratorNextStep(raxIterator *it, int noup) {
                 int todel = it->node->iscompr ? it->node->size : 1;
                 raxIteratorDelChars(it,todel);
 
-                /* Try visitng the next child if there was at least one
+                /* Try visiting the next child if there was at least one
                  * additional child. */
-                if (!it->node->iscompr && it->node->size > 1) {
+                if (!it->node->iscompr && it->node->size > (old_noup ? 0 : 1)) {
                     raxNode **cp = raxNodeFirstChildPtr(it->node);
                     int i = 0;
                     while (i < it->node->size) {
@@ -1276,6 +1301,8 @@ int raxIteratorPrevStep(raxIterator *it, int noup) {
     raxNode *orig_node = it->node;
 
     while(1) {
+        int old_noup = noup;
+
         /* Already on head? Can't go up, iteration finished. */
         if (!noup && it->node == it->rt->head) {
             it->flags |= RAX_ITER_EOF;
@@ -1297,9 +1324,9 @@ int raxIteratorPrevStep(raxIterator *it, int noup) {
         int todel = it->node->iscompr ? it->node->size : 1;
         raxIteratorDelChars(it,todel);
 
-        /* Try visiting the prev child if there was at least one
-         * additional child. */
-        if (!it->node->iscompr && it->node->size > 1) {
+        /* Try visiting the prev child if there is at least one
+         * child. */
+        if (!it->node->iscompr && it->node->size > (old_noup ? 0 : 1)) {
             raxNode **cp = raxNodeLastChildPtr(it->node);
             int i = it->node->size-1;
             while (i >= 0) {
@@ -1334,8 +1361,9 @@ int raxIteratorPrevStep(raxIterator *it, int noup) {
 
 /* Seek an iterator at the specified element.
  * Return 0 if the seek failed for syntax error or out of memory. Otherwise
- * 1 is returned. */
-int raxSeek(raxIterator *it, unsigned char *ele, size_t len, const char *op) {
+ * 1 is returned. When 0 is returned for out of memory, errno is set to
+ * the ENOMEM value. */
+int raxSeek(raxIterator *it, const char *op, unsigned char *ele, size_t len) {
     int eq = 0, lt = 0, gt = 0, first = 0, last = 0;
 
     it->stack.items = 0; /* Just resetting. Intialized by raxStart(). */
@@ -1358,6 +1386,7 @@ int raxSeek(raxIterator *it, unsigned char *ele, size_t len, const char *op) {
     } else if (op[0] == '$') {
         last = 1;
     } else {
+        errno = 0;
         return 0; /* Error. */
     }
 
@@ -1371,7 +1400,7 @@ int raxSeek(raxIterator *it, unsigned char *ele, size_t len, const char *op) {
     if (first) {
         /* Seeking the first key greater or equal to the empty string
          * is equivalent to seeking the smaller key available. */
-        return raxSeek(it,NULL,0,">=");
+        return raxSeek(it,">=",NULL,0);
     }
 
     if (last) {
@@ -1398,7 +1427,7 @@ int raxSeek(raxIterator *it, unsigned char *ele, size_t len, const char *op) {
         /* We found our node, since the key matches and we have an
          * "equal" condition. */
         if (!raxIteratorAddChars(it,ele,len)) return 0; /* OOM. */
-    } else {
+    } else if (lt || gt) {
         /* Exact key not found or eq flag not set. We have to set as current
          * key the one represented by the node we stopped at, and perform
          * a next/prev operation to seek. To reconstruct the key at this node
@@ -1490,14 +1519,18 @@ int raxSeek(raxIterator *it, unsigned char *ele, size_t len, const char *op) {
             if (lt && !raxIteratorPrevStep(it,0)) return 0;
             it->flags |= RAX_ITER_JUST_SEEKED; /* Ignore next call. */
         }
+    } else {
+        /* If we are here just eq was set but no match was found. */
+        it->flags |= RAX_ITER_EOF;
+        return 1;
     }
     return 1;
 }
 
 /* Go to the next element in the scope of the iterator 'it'.
  * If EOF (or out of memory) is reached, 0 is returned, otherwise 1 is
  * returned. In case 0 is returned because of OOM, errno is set to ENOMEM. */
-int raxNext(raxIterator *it, unsigned char *stop, size_t stoplen, char *op) {
+int raxNext(raxIterator *it) {
     if (!raxIteratorNextStep(it,0)) {
         errno = ENOMEM;
         return 0;
@@ -1512,7 +1545,7 @@ int raxNext(raxIterator *it, unsigned char *stop, size_t stoplen, char *op) {
 /* Go to the previous element in the scope of the iterator 'it'.
  * If EOF (or out of memory) is reached, 0 is returned, otherwise 1 is
  * returned. In case 0 is returned because of OOM, errno is set to ENOMEM. */
-int raxPrev(raxIterator *it, unsigned char *stop, size_t stoplen, char *op) {
+int raxPrev(raxIterator *it) {
     if (!raxIteratorPrevStep(it,0)) {
         errno = ENOMEM;
         return 0;
@@ -1524,6 +1557,87 @@ int raxPrev(raxIterator *it, unsigned char *stop, size_t stoplen, char *op) {
     return 1;
 }
 
+/* Perform a random walk starting in the current position of the iterator.
+ * Return 0 if the tree is empty or on out of memory. Otherwise 1 is returned
+ * and the iterator is set to the node reached after doing a random walk
+ * of 'steps' steps. If the 'steps' argument is 0, the random walk is performed
+ * using a random number of steps between 1 and two times the logarithm of
+ * the number of elements.
+ *
+ * NOTE: if you use this function to generate random elements from the radix
+ * tree, expect a disappointing distribution. A random walk produces good
+ * random elements if the tree is not sparse, however in the case of a radix
+ * tree certain keys will be reported much more often than others. At least
+ * this function should be able to expore every possible element eventually. */
+int raxRandomWalk(raxIterator *it, size_t steps) {
+    if (it->rt->numele == 0) {
+        it->flags |= RAX_ITER_EOF;
+        return 0;
+    }
+
+    if (steps == 0) {
+        size_t fle = floor(log(it->rt->numele));
+        fle *= 2;
+        steps = 1 + rand() % fle;
+    }
+
+    raxNode *n = it->node;
+    while(steps > 0 || !n->iskey) {
+        int numchildren = n->iscompr ? 1 : n->size;
+        int r = rand() % (numchildren+(n != it->rt->head));
+
+        if (r == numchildren) {
+            /* Go up to parent. */
+            n = raxStackPop(&it->stack);
+            int todel = n->iscompr ? n->size : 1;
+            raxIteratorDelChars(it,todel);
+        } else {
+            /* Select a random child. */
+            if (n->iscompr) {
+                if (!raxIteratorAddChars(it,n->data,n->size)) return 0;
+            } else {
+                if (!raxIteratorAddChars(it,n->data+r,1)) return 0;
+            }
+            raxNode **cp = raxNodeFirstChildPtr(n)+r;
+            if (!raxStackPush(&it->stack,n)) return 0;
+            memcpy(&n,cp,sizeof(n));
+        }
+        if (n->iskey) steps--;
+    }
+    it->node = n;
+    return 1;
+}
+
+/* Compare the key currently pointed by the iterator to the specified
+ * key according to the specified operator. Returns 1 if the comparison is
+ * true, otherwise 0 is returned. */
+int raxCompare(raxIterator *iter, const char *op, unsigned char *key, size_t key_len) {
+    int eq = 0, lt = 0, gt = 0;
+
+    if (op[0] == '=' || op[1] == '=') eq = 1;
+    if (op[1] == '>') gt = 1;
+    else if (op[1] == '<') lt = 1;
+    else if (op[1] != '=') return 0; /* Syntax error. */
+
+    size_t minlen = key_len < iter->key_len ? key_len : iter->key_len;
+    int cmp = memcmp(iter->key,key,minlen);
+
+    /* Handle == */
+    if (lt == 0 && gt == 0) return cmp == 0 && key_len == iter->key_len;
+
+    /* Handle >, >=, <, <= */
+    if (cmp == 0) {
+        /* Same prefix: longer wins. */
+        if (eq && key_len == iter->key_len) return 1;
+        else if (lt) return iter->key_len < key_len;
+        else if (gt) return iter->key_len > key_len;
+    } if (cmp > 0) {
+        return gt ? 1 : 0;
+    } else /* (cmp < 0) */ {
+        return lt ? 1 : 0;
+    }
+}
+
 /* Free the iterator. */
 void raxStop(raxIterator *it) {
     if (it->key != it->key_static_string) rax_free(it->key);
@@ -1613,233 +1727,4 @@ void raxDebugShowNode(const char *msg, raxNode *n) {
     fflush(stdout);
 }
 
-#ifdef BENCHMARK_MAIN
-#include <stdio.h>
-#include <sys/time.h>
-
-/* This is a simple Feistel network in order to turn every possible
- * uint32_t input into another "randomly" looking uint32_t. It is a
- * one to one map so there are no repetitions. */
-static uint32_t int2int(uint32_t input) {
-    uint16_t l = input & 0xffff;
-    uint16_t r = input >> 16;
-    for (int i = 0; i < 8; i++) {
-        uint16_t nl = r;
-        uint16_t F = (((r * 31) + (r >> 5) + 7 * 371) ^ r) & 0xffff;
-        r = l ^ F;
-        l = nl;
-    }
-    return (r<<16)|l;
-}
-
-/* Turn an uint32_t integer into an alphanumerical key and return its
- * length. This function is used in order to generate keys that have
- * a large charset, so that the radix tree can be testsed with many
- * children per node. */
-static size_t int2alphakey(char *s, size_t maxlen, uint32_t i) {
-    const char *set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
-                      "abcdefghijklmnopqrstuvwxyz"
-                      "0123456789";
-    const size_t setlen = 62;
-
-    if (maxlen == 0) return 0;
-    maxlen--; /* Space for null term char. */
-    size_t len = 0;
-    while(len < maxlen) {
-        s[len++] = set[i%setlen];
-        i /= setlen;
-        if (i == 0) break;
-    }
-    s[len] = '\0';
-    return len;
-}
-
-/* Return the UNIX time in microseconds */
-static long long ustime(void) {
-    struct timeval tv;
-    long long ust;
-
-    gettimeofday(&tv, NULL);
-    ust = ((long long)tv.tv_sec)*1000000;
-    ust += tv.tv_usec;
-    return ust;
-}
-
-/* Turn the integer 'i' into a key according to 'mode'.
- * mode = 0, just represents the integer as a string.
- * mode = 1, turn it into a random-looking alphanumerical string
- *           according to the int2alphakey() function. */
-static size_t int2key(char *s, size_t maxlen, uint32_t i, int mode) {
-    if (mode == 0) {
-        return snprintf(s,maxlen,"%lu",(unsigned long)i);
-    } else {
-        i = int2int(i);
-        return int2alphakey(s,maxlen,i);
-    }
-}
-
-int main(void) {
-    for (int mode = 0; mode < 2; mode++) {
-        printf("Benchmark with %s keys:\n",
-            (mode == 0) ? "integer" : "alphanumerical");
-        rax *t = raxNew();
-        long long start = ustime();
-        for (int i = 0; i < 5000000; i++) {
-            char buf[64];
-            int len = int2key(buf,sizeof(buf),i,mode);
-            raxInsert(t,(unsigned char*)buf,len,(void*)(long)i);
-        }
-        printf("Insert: %f\n", (double)(ustime()-start)/1000000);
-        printf("%llu total nodes\n", (unsigned long long)t->numnodes);
-        printf("%llu total elements\n", (unsigned long long)t->numele);
-
-        start = ustime();
-        for (int i = 0; i < 5000000; i++) {
-            char buf[64];
-            int len = int2key(buf,sizeof(buf),i,mode);
-            void *data = raxFind(t,(unsigned char*)buf,len);
-            if (data != (void*)(long)i) {
-                printf("Issue with %s: %p instead of %p\n", buf,
-                    data, (void*)(long)i);
-            }
-        }
-        printf("Lookup: %f\n", (double)(ustime()-start)/1000000);
-
-        start = ustime();
-        for (int i = 0; i < 5000000; i++) {
-            char buf[64];
-            int r = rand() % 5000000;
-            int len = int2key(buf,sizeof(buf),r,mode);
-            void *data = raxFind(t,(unsigned char*)buf,len);
-            if (data != (void*)(long)r) {
-                printf("Issue with %s: %p instead of %p\n", buf,
-                    data, (void*)(long)r);
-            }
-        }
-        printf("Random lookup: %f\n", (double)(ustime()-start)/1000000);
-
-        start = ustime();
-        int count = 0;
-        for (int i = 0; i < 5000000; i++) {
-            char buf[64];
-            int len = int2key(buf,sizeof(buf),i,mode);
-            buf[i%len] = '!'; /* "!" is never set into keys. */
-            void *data = raxFind(t,(unsigned char*) buf,len);
-            if (data != (void*)(long)i) count++;
-        }
-        printf("Failed lookup: %f\n", (double)(ustime()-start)/1000000);
-
-        start = ustime();
-        for (int i = 0; i < 5000000; i++) {
-            char buf[64];
-            int len = int2key(buf,sizeof(buf),i,mode);
-            int retval = raxRemove(t,(unsigned char*)buf,len);
-            assert(retval == 1);
-        }
-        printf("Deletion: %f\n", (double)(ustime()-start)/1000000);
-
-        printf("%llu total nodes\n", (unsigned long long)t->numnodes);
-        printf("%llu total elements\n", (unsigned long long)t->numele);
-        raxFree(t);
-    }
-    return 0;
-}
-#endif
-
-#ifdef TEST_MAIN
-#include <stdio.h>
-#include <time.h>
-
-int main(void) {
-    printf("notfound = %p\n", raxNotFound);
-    rax *t = raxNew();
-    char *toadd[] = {"alligator","alien","baloon","chromodynamic","romane","romanus","romulus","rubens","ruber","rubicon","rubicundus","all","rub","ba",NULL};
-
-    srand(time(NULL));
-    for (int x = 0; x < 10000; x++) rand();
-
-    long items = 0;
-    while(toadd[items] != NULL) items++;
-
-    for (long i = 0; i < items; i++) {
-        raxInsert(t,(unsigned char*)toadd[i],strlen(toadd[i]),(void*)i);
-        printf("Added %s\n", toadd[i]);
-    }
-    raxShow(t);
-
-    raxIterator iter;
-    raxStart(&iter,t);
-
-    // OK: all this tests will need to go in the Rax unit test.
-    // raxSeek(&iter,(unsigned char*)"rpxxx",5,"<=");
-    // raxSeek(&iter,(unsigned char*)"rom",3,">=");
-    // raxSeek(&iter,(unsigned char*)"rub",3,">=");
-    // raxSeek(&iter,(unsigned char*)"rub",3,">");
-    // raxSeek(&iter,(unsigned char*)"rub",3,"<");
-    // raxSeek(&iter,(unsigned char*)"rom",3,">");
-    // raxSeek(&iter,(unsigned char*)"chro",4,">");
-    // raxSeek(&iter,(unsigned char*)"chro",4,"<");
-    // raxSeek(&iter,(unsigned char*)"chromz",6,"<");
-    // raxSeek(&iter,NULL,0,"^");
-    // raxSeek(&iter,"zorro",5,"<=");
-    // raxSeek(&iter,"zorro",5,"<");
-    // raxSeek(&iter,NULL,0,"$");
-
-    // STILL TO TEST
-    raxSeek(&iter,(unsigned char*)"ro",2,">=");
-    printf("EOF: %d\n", (iter.flags & RAX_ITER_EOF) != 0);
-
-    printf("SEEKED: %.*s, val %p\n", (int)iter.key_len,
-                                     (char*)iter.key,
-                                     iter.data);
-
-    printf("NEXT\n");
-    while(raxNext(&iter,NULL,0,NULL)) {
-        printf("--- key: %.*s, val %p\n", (int)iter.key_len,
-                                      (char*)iter.key,
-                                      iter.data);
-    }
-
-    printf("After EOF element is: %.*s\n", (int)iter.key_len,
-                                      (char*)iter.key);
-    printf("~~~~~~~~~~~~~~\n");
-
-    printf("PREV\n");
-    raxSeek(&iter,iter.key,iter.key_len,"==");
-    while(raxPrev(&iter,NULL,0,NULL)) {
-        printf("--- key: %.*s, val %p\n", (int)iter.key_len,
-                                      (char*)iter.key,
-                                      iter.data);
-    }
-
-    printf("After EOF element is: %.*s\n", (int)iter.key_len,
-                                      (char*)iter.key);
-    raxStop(&iter);
 
-#if 0
-    raxStop(&iter);
-#endif
-    exit(0);
-
-    int rnum = rand();
-    int survivor = rnum % items;
-
-#if 1
-    printf("Removing everything but %s in random order\n", toadd[survivor]);
-    for (long i = 0; i < 1000; i++) {
-        int r = rand() % items;
-        if (r == survivor) continue;
-        raxRemove(t,(unsigned char*)toadd[r],strlen(toadd[r]));
-    }
-#else
-    printf("Removing rubicon\n");
-    raxRemove(t,(unsigned char*)"rubicon",7);
-#endif
-
-    printf("%llu total nodes\n", (unsigned long long)t->numnodes);
-    printf("%llu total elements\n", (unsigned long long)t->numele);
-
-    raxShow(t);
-    raxFree(t);
-}
-#endif