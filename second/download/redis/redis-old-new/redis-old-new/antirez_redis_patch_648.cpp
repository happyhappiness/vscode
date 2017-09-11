@@ -1222,6 +1222,8 @@ int ziplistTest(int argc, char **argv) {
     zl = createIntList();
     ziplistRepr(zl);
 
+    zfree(zl);
+
     zl = createList();
     ziplistRepr(zl);
 
@@ -1237,6 +1239,8 @@ int ziplistTest(int argc, char **argv) {
     zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
+    zfree(zl);
+
     printf("Get element at index 3:\n");
     {
         zl = createList();
@@ -1252,6 +1256,7 @@ int ziplistTest(int argc, char **argv) {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index 4 (out of range):\n");
@@ -1265,6 +1270,7 @@ int ziplistTest(int argc, char **argv) {
             return 1;
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index -1 (last element):\n");
@@ -1282,6 +1288,7 @@ int ziplistTest(int argc, char **argv) {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index -4 (first element):\n");
@@ -1299,6 +1306,7 @@ int ziplistTest(int argc, char **argv) {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index -5 (reverse out of range):\n");
@@ -1312,6 +1320,7 @@ int ziplistTest(int argc, char **argv) {
             return 1;
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 0 to end:\n");
@@ -1329,6 +1338,7 @@ int ziplistTest(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 1 to end:\n");
@@ -1346,6 +1356,7 @@ int ziplistTest(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 2 to end:\n");
@@ -1363,6 +1374,7 @@ int ziplistTest(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate starting out of range:\n");
@@ -1375,6 +1387,7 @@ int ziplistTest(int argc, char **argv) {
             printf("ERROR\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate from back to front:\n");
@@ -1392,6 +1405,7 @@ int ziplistTest(int argc, char **argv) {
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate from back to front, deleting all items:\n");
@@ -1410,41 +1424,47 @@ int ziplistTest(int argc, char **argv) {
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
@@ -1469,6 +1489,7 @@ int ziplistTest(int argc, char **argv) {
         }
         printf("\n");
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Regression test for >255 byte strings:\n");
@@ -1488,6 +1509,7 @@ int ziplistTest(int argc, char **argv) {
         assert(ziplistGet(p,&entry,&elen,&value));
         assert(strncmp(v2,(char*)entry,elen) == 0);
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Regression test deleting next to last entries:\n");
@@ -1526,6 +1548,7 @@ int ziplistTest(int argc, char **argv) {
         assert(e[1].prevrawlensize == 5);
 
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Create long list and check indices:\n");
@@ -1547,6 +1570,7 @@ int ziplistTest(int argc, char **argv) {
             assert(999-i == value);
         }
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Compare strings with ziplist entries:\n");
@@ -1572,6 +1596,7 @@ int ziplistTest(int argc, char **argv) {
             return 1;
         }
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Merge test:\n");
@@ -1646,6 +1671,7 @@ int ziplistTest(int argc, char **argv) {
             return 1;
         }
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Stress with random payloads of different encoding:\n");