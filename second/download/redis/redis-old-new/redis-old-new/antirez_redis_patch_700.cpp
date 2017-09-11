@@ -397,7 +397,7 @@ void incrbyfloatCommand(redisClient *c) {
         addReplyError(c,"increment would produce NaN or Infinity");
         return;
     }
-    new = createStringObjectFromLongDouble(value);
+    new = createStringObjectFromLongDouble(value,1);
     if (o)
         dbOverwrite(c->db,c->argv[1],new);
     else