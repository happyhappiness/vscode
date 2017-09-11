@@ -567,7 +567,7 @@ void hincrbyfloatCommand(client *c) {
     if (hashTypeGetValue(o,c->argv[2]->ptr,&vstr,&vlen,&ll) == C_OK) {
         if (vstr) {
             if (string2d((char*)vstr,vlen,&value) == 0) {
-                addReplyError(c,"hash value is not an integer");
+                addReplyError(c,"hash value is not a float");
                 return;
             }
         } else {