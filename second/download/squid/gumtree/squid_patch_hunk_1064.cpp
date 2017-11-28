     }
 
     return true;
 }
 
 void
-Format::Format::dump(StoreEntry * entry, const char *directiveName)
+Format::Format::dump(StoreEntry * entry, const char *directiveName, bool eol) const
 {
     debugs(46, 4, HERE);
 
     // loop rather than recursing to conserve stack space.
-    for (Format *fmt = this; fmt; fmt = fmt->next) {
+    for (const Format *fmt = this; fmt; fmt = fmt->next) {
         debugs(46, 3, HERE << "Dumping format definition for " << fmt->name);
-        storeAppendPrintf(entry, "%s %s ", directiveName, fmt->name);
+        if (directiveName)
+            storeAppendPrintf(entry, "%s %s ", directiveName, fmt->name);
 
         for (Token *t = fmt->format; t; t = t->next) {
             if (t->type == LFT_STRING)
                 storeAppendPrintf(entry, "%s", t->data.string);
             else {
                 char argbuf[256];
