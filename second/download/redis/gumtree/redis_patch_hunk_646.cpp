         "{tail offset %u}\n",
         intrev32ifbe(ZIPLIST_BYTES(zl)),
         intrev16ifbe(ZIPLIST_LENGTH(zl)),
         intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl)));
     p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
-        entry = zipEntry(p);
+        zipEntry(p, &entry);
         printf(
             "{"
                 "addr 0x%08lx, "
                 "index %2d, "
                 "offset %5ld, "
                 "rl: %5u, "
