     if ((t = strrchr(buf, ',')))
         *t = '\0';
 
     return buf;
 }
 
-static const char *
-describeTimestamps(const StoreEntry * entry)
-{
-    LOCAL_ARRAY(char, buf, 256);
-    snprintf(buf, 256, "LV:%-9d LU:%-9d LM:%-9d EX:%-9d",
-             (int) entry->timestamp,
-             (int) entry->lastref,
-             (int) entry->lastmod,
-             (int) entry->expires);
-    return buf;
-}
-
 static void
 statStoreEntry(MemBuf * mb, StoreEntry * e)
 {
     MemObject *mem = e->mem_obj;
     mb->Printf("KEY %s\n", e->getMD5Text());
     mb->Printf("\t%s\n", describeStatuses(e));
     mb->Printf("\t%s\n", storeEntryFlags(e));
-    mb->Printf("\t%s\n", describeTimestamps(e));
+    mb->Printf("\t%s\n", e->describeTimestamps());
     mb->Printf("\t%d locks, %d clients, %d refs\n",
-               (int) e->lock_count,
+               (int) e->locks(),
                storePendingNClients(e),
                (int) e->refcount);
     mb->Printf("\tSwap Dir %d, File %#08X\n",
                e->swap_dirn, e->swap_filen);
 
     if (mem != NULL)
