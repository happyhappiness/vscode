@@ -284,7 +284,6 @@ static void cliIntegrateHelp(void) {
                 break;
         }
         if (i != helpEntriesLen) continue;
-        printf("%s\n", cmdname);
 
         helpEntriesLen++;
         helpEntries = zrealloc(helpEntries,sizeof(helpEntry)*helpEntriesLen);
@@ -314,8 +313,6 @@ static void cliIntegrateHelp(void) {
         new->org = ch;
     }
     freeReplyObject(reply);
-
-    printf("%s\n", helpEntries[80].full);
 }
 
 /* Output command help to stdout. */