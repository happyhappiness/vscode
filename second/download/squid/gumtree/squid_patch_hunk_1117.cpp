     storeAppendPrintf(sentry, "%-46.46s %9s %7s %5s %s\n",  /* Max between 16 (IPv4) or 46 (IPv6)   */
                       "Network",
                       "recv/sent",
                       "RTT",
                       "Hops",
                       "Hostnames");
-    list = (netdbEntry **)xcalloc(memInUse(MEM_NETDBENTRY), sizeof(netdbEntry *));
+    list = (netdbEntry **)xcalloc(netdbEntry::UseCount(), sizeof(netdbEntry *));
     i = 0;
     hash_first(addr_table);
 
     while ((n = (netdbEntry *) hash_next(addr_table))) {
         *(list + i) = n;
         ++i;
     }
 
-    if (i != memInUse(MEM_NETDBENTRY))
+    if (i != netdbEntry::UseCount())
         debugs(38, DBG_CRITICAL, "WARNING: netdb_addrs count off, found " << i <<
-               ", expected " << memInUse(MEM_NETDBENTRY));
+               ", expected " << netdbEntry::UseCount());
 
     qsort((char *) list,
           i,
           sizeof(netdbEntry *),
           sortByRtt);
 
