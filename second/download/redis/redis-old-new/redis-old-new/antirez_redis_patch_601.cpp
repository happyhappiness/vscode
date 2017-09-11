@@ -1945,6 +1945,7 @@ static void statMode(void) {
         /* Children */
         aux = getLongInfoField(reply->str,"bgsave_in_progress");
         aux |= getLongInfoField(reply->str,"aof_rewrite_in_progress") << 1;
+        aux |= getLongInfoField(reply->str,"loading") << 2;
         switch(aux) {
         case 0: break;
         case 1:
@@ -1956,6 +1957,9 @@ static void statMode(void) {
         case 3:
             printf("SAVE+AOF");
             break;
+        case 4:
+            printf("LOAD");
+            break;
         }
 
         printf("\n");