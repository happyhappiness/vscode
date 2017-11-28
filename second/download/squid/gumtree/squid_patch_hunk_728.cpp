 
     debugs(3, DBG_CRITICAL, "WARNING: Unknown bytes unit '" << unit << "'");
 
     return 0;
 }
 
-/*****************************************************************************
- * Max
- *****************************************************************************/
-
 static void
-dump_wordlist(StoreEntry * entry, wordlist *words)
+dump_SBufList(StoreEntry * entry, const SBufList &words)
 {
-    for (wordlist *word = words; word; word = word->next)
-        // XXX: use something like ConfigParser::QuoteString() here
-        storeAppendPrintf(entry, "%s ", word->key);
+    for (SBufList::const_iterator i = words.begin(); i != words.end(); ++i) {
+        entry->append(i->rawContent(), i->length());
+        entry->append(" ",1);
+    }
+    entry->append("\n",1);
 }
 
 static void
 dump_acl(StoreEntry * entry, const char *name, ACL * ae)
 {
     while (ae != NULL) {
         debugs(3, 3, "dump_acl: " << name << " " << ae->name);
         storeAppendPrintf(entry, "%s %s %s %s ",
                           name,
                           ae->name,
                           ae->typeString(),
                           ae->flags.flagsStr());
-        wordlist *w = ae->dump();
-        dump_wordlist(entry, w);
-
-        storeAppendPrintf(entry, "\n");
-        wordlistDestroy(&w);
+        dump_SBufList(entry, ae->dump());
         ae = ae->next;
     }
 }
 
 static void
 parse_acl(ACL ** ae)
