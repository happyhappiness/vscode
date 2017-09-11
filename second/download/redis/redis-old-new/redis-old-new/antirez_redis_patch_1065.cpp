@@ -1324,7 +1324,6 @@ static void findBigKeys(void) {
         } else if (!strcmp(reply2->str,"none")) {
             freeReplyObject(reply1);
             freeReplyObject(reply2);
-            freeReplyObject(reply3);
             continue;
         } else {
             fprintf(stderr, "Unknown key type '%s' for key '%s'\n",