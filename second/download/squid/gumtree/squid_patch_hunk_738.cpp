 static void
 dump_b_size_t(StoreEntry * entry, const char *name, size_t var)
 {
     storeAppendPrintf(entry, "%s %d %s\n", name, (int) var, B_BYTES_STR);
 }
 
-#if !USE_DNSHELPER
 static void
 dump_b_ssize_t(StoreEntry * entry, const char *name, ssize_t var)
 {
     storeAppendPrintf(entry, "%s %d %s\n", name, (int) var, B_BYTES_STR);
 }
-#endif
 
 #if UNUSED_CODE
 static void
 dump_kb_size_t(StoreEntry * entry, const char *name, size_t var)
 {
     storeAppendPrintf(entry, "%s %d %s\n", name, (int) var, B_KBYTES_STR);
