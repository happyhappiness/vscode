@@ -516,7 +516,7 @@ void _serverAssertPrintClientInfo(client *c) {
         if (c->argv[j]->type == OBJ_STRING && sdsEncodedObject(c->argv[j])) {
             arg = (char*) c->argv[j]->ptr;
         } else {
-            snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
+            snprintf(buf,sizeof(buf),"Object type: %u, encoding: %u",
                 c->argv[j]->type, c->argv[j]->encoding);
             arg = buf;
         }