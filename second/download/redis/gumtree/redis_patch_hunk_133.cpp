             sdslen(x) == 33 &&
             memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0)
 
         sdsfree(x);
         x = sdscatprintf(sdsempty(),"%d",123);
         test_cond("sdscatprintf() seems working in the base case",
-            sdslen(x) == 3 && memcmp(x,"123\0",4) ==0)
+            sdslen(x) == 3 && memcmp(x,"123\0",4) == 0)
+
+        sdsfree(x);
+        x = sdsnew("--");
+        x = sdscatfmt(x, "Hello %s World %I,%I--", "Hi!", LLONG_MIN,LLONG_MAX);
+        test_cond("sdscatfmt() seems working in the base case",
+            sdslen(x) == 60 &&
+            memcmp(x,"--Hello Hi! World -9223372036854775808,"
+                     "9223372036854775807--",60) == 0)
+
+        sdsfree(x);
+        x = sdsnew("--");
+        x = sdscatfmt(x, "%u,%U--", UINT_MAX, ULLONG_MAX);
+        test_cond("sdscatfmt() seems working with unsigned numbers",
+            sdslen(x) == 35 &&
+            memcmp(x,"--4294967295,18446744073709551615--",35) == 0)
 
         sdsfree(x);
-        x = sdstrim(sdsnew("xxciaoyyy"),"xy");
+        x = sdsnew("xxciaoyyy");
+        sdstrim(x,"xy");
         test_cond("sdstrim() correctly trims characters",
             sdslen(x) == 4 && memcmp(x,"ciao\0",5) == 0)
 
-        y = sdsrange(sdsdup(x),1,1);
+        y = sdsdup(x);
+        sdsrange(y,1,1);
         test_cond("sdsrange(...,1,1)",
             sdslen(y) == 1 && memcmp(y,"i\0",2) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),1,-1);
+        y = sdsdup(x);
+        sdsrange(y,1,-1);
         test_cond("sdsrange(...,1,-1)",
             sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),-2,-1);
+        y = sdsdup(x);
+        sdsrange(y,-2,-1);
         test_cond("sdsrange(...,-2,-1)",
             sdslen(y) == 2 && memcmp(y,"ao\0",3) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),2,1);
+        y = sdsdup(x);
+        sdsrange(y,2,1);
         test_cond("sdsrange(...,2,1)",
             sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),1,100);
+        y = sdsdup(x);
+        sdsrange(y,1,100);
         test_cond("sdsrange(...,1,100)",
             sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),100,100);
+        y = sdsdup(x);
+        sdsrange(y,100,100);
         test_cond("sdsrange(...,100,100)",
             sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
 
         sdsfree(y);
         sdsfree(x);
         x = sdsnew("foo");
