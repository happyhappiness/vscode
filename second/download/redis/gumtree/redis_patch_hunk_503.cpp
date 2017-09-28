 }
 
 void dictDisableResize(void) {
     dict_can_resize = 0;
 }
 
-#if 0
-
-/* The following is code that we don't use for Redis currently, but that is part
-of the library. */
-
-/* ----------------------- Debugging ------------------------*/
+/* ------------------------------- Debugging ---------------------------------*/
 
 #define DICT_STATS_VECTLEN 50
-static void _dictPrintStatsHt(dictht *ht) {
+size_t _dictGetStatsHt(char *buf, size_t bufsize, dictht *ht, int tableid) {
     unsigned long i, slots = 0, chainlen, maxchainlen = 0;
     unsigned long totchainlen = 0;
     unsigned long clvector[DICT_STATS_VECTLEN];
+    size_t l = 0;
 
     if (ht->used == 0) {
-        printf("No stats available for empty dictionaries\n");
-        return;
+        return snprintf(buf,bufsize,
+            "No stats available for empty dictionaries\n");
     }
 
+    /* Compute stats. */
     for (i = 0; i < DICT_STATS_VECTLEN; i++) clvector[i] = 0;
     for (i = 0; i < ht->size; i++) {
         dictEntry *he;
 
         if (ht->table[i] == NULL) {
             clvector[0]++;
