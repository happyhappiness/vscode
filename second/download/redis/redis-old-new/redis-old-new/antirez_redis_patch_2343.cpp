@@ -40,6 +40,7 @@
 #include <string.h>
 #include <stdarg.h>
 #include <assert.h>
+#include <limits.h>
 
 #include "dict.h"
 #include "zmalloc.h"
@@ -74,7 +75,7 @@ static void _dictFree(void *ptr) {
 /* -------------------------- private prototypes ---------------------------- */
 
 static int _dictExpandIfNeeded(dict *ht);
-static unsigned int _dictNextPower(unsigned int size);
+static unsigned long _dictNextPower(unsigned long size);
 static int _dictKeyIndex(dict *ht, const void *key);
 static int _dictInit(dict *ht, dictType *type, void *privDataPtr);
 
@@ -152,10 +153,10 @@ int dictResize(dict *ht)
 }
 
 /* Expand or create the hashtable */
-int dictExpand(dict *ht, unsigned int size)
+int dictExpand(dict *ht, unsigned long size)
 {
     dict n; /* the new hashtable */
-    unsigned int realsize = _dictNextPower(size), i;
+    unsigned long realsize = _dictNextPower(size), i;
 
     /* the size is invalid if it is smaller than the number of
      * elements already inside the hashtable */
@@ -286,7 +287,7 @@ int dictDeleteNoFree(dict *ht, const void *key) {
 /* Destroy an entire hash table */
 int _dictClear(dict *ht)
 {
-    unsigned int i;
+    unsigned long i;
 
     /* Free all the elements */
     for (i = 0; i < ht->size && ht->used > 0; i++) {
@@ -413,12 +414,11 @@ static int _dictExpandIfNeeded(dict *ht)
 }
 
 /* Our hash table capability is a power of two */
-static unsigned int _dictNextPower(unsigned int size)
+static unsigned long _dictNextPower(unsigned long size)
 {
-    unsigned int i = DICT_HT_INITIAL_SIZE;
+    unsigned long i = DICT_HT_INITIAL_SIZE;
 
-    if (size >= 2147483648U)
-        return 2147483648U;
+    if (size >= LONG_MAX) return LONG_MAX;
     while(1) {
         if (i >= size)
             return i;
@@ -455,9 +455,9 @@ void dictEmpty(dict *ht) {
 
 #define DICT_STATS_VECTLEN 50
 void dictPrintStats(dict *ht) {
-    unsigned int i, slots = 0, chainlen, maxchainlen = 0;
-    unsigned int totchainlen = 0;
-    unsigned int clvector[DICT_STATS_VECTLEN];
+    unsigned long i, slots = 0, chainlen, maxchainlen = 0;
+    unsigned long totchainlen = 0;
+    unsigned long clvector[DICT_STATS_VECTLEN];
 
     if (ht->used == 0) {
         printf("No stats available for empty dictionaries\n");
@@ -485,16 +485,16 @@ void dictPrintStats(dict *ht) {
         totchainlen += chainlen;
     }
     printf("Hash table stats:\n");
-    printf(" table size: %d\n", ht->size);
-    printf(" number of elements: %d\n", ht->used);
-    printf(" different slots: %d\n", slots);
-    printf(" max chain length: %d\n", maxchainlen);
+    printf(" table size: %ld\n", ht->size);
+    printf(" number of elements: %ld\n", ht->used);
+    printf(" different slots: %ld\n", slots);
+    printf(" max chain length: %ld\n", maxchainlen);
     printf(" avg chain length (counted): %.02f\n", (float)totchainlen/slots);
     printf(" avg chain length (computed): %.02f\n", (float)ht->used/slots);
     printf(" Chain length distribution:\n");
     for (i = 0; i < DICT_STATS_VECTLEN-1; i++) {
         if (clvector[i] == 0) continue;
-        printf("   %s%d: %d (%.02f%%)\n",(i == DICT_STATS_VECTLEN-1)?">= ":"", i, clvector[i], ((float)clvector[i]/ht->size)*100);
+        printf("   %s%ld: %ld (%.02f%%)\n",(i == DICT_STATS_VECTLEN-1)?">= ":"", i, clvector[i], ((float)clvector[i]/ht->size)*100);
     }
 }
 