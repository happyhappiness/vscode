@@ -68,26 +68,30 @@ int sortPointers(const void *a, const void *b) {
     return la-lb;
 }
 
-void stressGetKeys(dict *d, int times) {
+void stressGetKeys(dict *d, int times, int *perfect_run, int *approx_run) {
     int j;
+
     dictEntry **des = zmalloc(sizeof(dictEntry*)*dictSize(d));
     for (j = 0; j < times; j++) {
         int requested = rand() % (dictSize(d)+1);
         int returned = dictGetSomeKeys(d, des, requested);
-        if (requested != returned) {
-            printf("*** ERROR! Req: %d, Ret: %d\n", requested, returned);
-            exit(1);
-        }
+        int dup = 0;
+
         qsort(des,returned,sizeof(dictEntry*),sortPointers);
         if (returned > 1) {
             int i;
             for (i = 0; i < returned-1; i++) {
-                if (des[i] == des[i+1]) {
-                    printf("*** ERROR! Duplicated element detected\n");
-                    exit(1);
-                }
+                if (des[i] == des[i+1]) dup++;
             }
         }
+
+        if (requested == returned && dup == 0) {
+            (*perfect_run)++;
+        } else {
+            (*approx_run)++;
+            printf("Requested, returned, duplicated: %d %d %d\n",
+                requested, returned, dup);
+        }
     }
     zfree(des);
 }
@@ -113,18 +117,24 @@ int main(void) {
     dictRelease(d);
 
     d = dictCreate(&dictTypeTest,NULL);
-    printf("Getkeys stress test\n");
+
+    printf("Stress testing dictGetSomeKeys\n");
+    int perfect_run = 0, approx_run = 0;
 
     for (i = 0; i < MAX2; i++) {
         dictAdd(d,(void*)i,NULL);
-        stressGetKeys(d,100);
+        stressGetKeys(d,100,&perfect_run,&approx_run);
     }
 
     for (i = 0; i < MAX2; i++) {
         dictDelete(d,(void*)i);
         dictResize(d);
-        stressGetKeys(d,100);
+        stressGetKeys(d,100,&perfect_run,&approx_run);
     }
+
+    printf("dictGetSomeKey, %d perfect runs, %d approximated runs\n",
+        perfect_run, approx_run);
+
     dictRelease(d);
 
     printf("TEST PASSED!\n");