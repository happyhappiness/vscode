@@ -488,14 +488,85 @@ sds *sdssplitargs(char *line, int *argc) {
 
 int main(void) {
     {
-        sds x = sdsnew("foo");
-
-        /* SDS creation and length */
-        test_cond("Can create a string and obtain the length",
-            sdslen(x) == 3 && memcmp(x,"foo",3) == 0)
-
-        /* Nul term checking */
-        test_cond("The string contains the nul term", x[3] == '\0')
+        sds x = sdsnew("foo"), y;
+
+        test_cond("Create a string and obtain the length",
+            sdslen(x) == 3 && memcmp(x,"foo\0",4) == 0)
+
+        sdsfree(x);
+        x = sdsnewlen("foo",2);
+        test_cond("Create a string with specified length",
+            sdslen(x) == 2 && memcmp(x,"fo\0",3) == 0)
+
+        x = sdscat(x,"bar");
+        test_cond("Strings concatenation",
+            sdslen(x) == 5 && memcmp(x,"fobar\0",6) == 0);
+
+        x = sdscpy(x,"a");
+        test_cond("sdscpy() against an originally longer string",
+            sdslen(x) == 1 && memcmp(x,"a\0",2) == 0)
+
+        x = sdscpy(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
+        test_cond("sdscpy() against an originally shorter string",
+            sdslen(x) == 33 &&
+            memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0)
+
+        sdsfree(x);
+        x = sdscatprintf(sdsempty(),"%d",123);
+        test_cond("sdscatprintf() seems working in the base case",
+            sdslen(x) == 3 && memcmp(x,"123\0",4) ==0)
+
+        sdsfree(x);
+        x = sdstrim(sdsnew("xxciaoyyy"),"xy");
+        test_cond("sdstrim() correctly trims characters",
+            sdslen(x) == 4 && memcmp(x,"ciao\0",5) == 0)
+
+        y = sdsrange(sdsdup(x),1,1);
+        test_cond("sdsrange(...,1,1)",
+            sdslen(y) == 1 && memcmp(y,"i\0",2) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),1,-1);
+        test_cond("sdsrange(...,1,-1)",
+            sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),-2,-1);
+        test_cond("sdsrange(...,-2,-1)",
+            sdslen(y) == 2 && memcmp(y,"ao\0",3) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),2,1);
+        test_cond("sdsrange(...,2,1)",
+            sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),1,100);
+        test_cond("sdsrange(...,1,100)",
+            sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),100,100);
+        test_cond("sdsrange(...,100,100)",
+            sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("foo");
+        y = sdsnew("foa");
+        test_cond("sdscmp(foo,foa)", sdscmp(x,y) > 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("bar");
+        y = sdsnew("bar");
+        test_cond("sdscmp(bar,bar)", sdscmp(x,y) == 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("aar");
+        y = sdsnew("bar");
+        test_cond("sdscmp(bar,bar)", sdscmp(x,y) < 0)
     }
     test_report()
 }