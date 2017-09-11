@@ -1183,6 +1183,7 @@ static void findBigKeys(void) {
     unsigned long long samples = 0;
     redisReply *reply1, *reply2, *reply3 = NULL;
     char *sizecmd, *typename[] = {"string","list","set","hash","zset"};
+    char *typeunit[] = {"bytes","items","members","fields","members"};
     int type;
 
     printf("\n# Press ctrl+c when you have had enough of it... :)\n");
@@ -1234,9 +1235,10 @@ static void findBigKeys(void) {
         reply3 = redisCommand(context,"%s %s", sizecmd, reply1->str);
         if (reply3 && reply3->type == REDIS_REPLY_INTEGER) {
             if (biggest[type] < reply3->integer) {
-                printf("[%6s] %s | biggest so far with size %llu\n",
+                printf("Biggest %-6s found so far '%s' with %llu %s.\n",
                     typename[type], reply1->str,
-                    (unsigned long long) reply3->integer);
+                    (unsigned long long) reply3->integer,
+                    typeunit[type]);
                 biggest[type] = reply3->integer;
             }
         }