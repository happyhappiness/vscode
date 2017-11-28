 
 /*****************************************************************************
  * Max
  *****************************************************************************/
 
 static void
-dump_acl(StoreEntry * entry, const char *name, ACL * ae)
+dump_wordlist(StoreEntry * entry, wordlist *words)
 {
-    wordlist *w;
-    wordlist *v;
+    for (wordlist *word = words; word; word = word->next)
+        // XXX: use something like ConfigParser::QuoteString() here
+        storeAppendPrintf(entry, "%s ", word->key);
+}
 
+static void
+dump_acl(StoreEntry * entry, const char *name, ACL * ae)
+{
     while (ae != NULL) {
         debugs(3, 3, "dump_acl: " << name << " " << ae->name);
-        storeAppendPrintf(entry, "%s %s %s ",
+        storeAppendPrintf(entry, "%s %s %s %s ",
                           name,
                           ae->name,
-                          ae->typeString());
-        v = w = ae->dump();
-
-        while (v != NULL) {
-            debugs(3, 3, "dump_acl: " << name << " " << ae->name << " " << v->key);
-            storeAppendPrintf(entry, "%s ", v->key);
-            v = v->next;
-        }
+                          ae->typeString(),
+                          ae->flags.flagsStr());
+        wordlist *w = ae->dump();
+        dump_wordlist(entry, w);
 
         storeAppendPrintf(entry, "\n");
         wordlistDestroy(&w);
         ae = ae->next;
     }
 }
