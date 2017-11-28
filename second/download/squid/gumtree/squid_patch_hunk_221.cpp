                       "Hops",
                       "Hostnames");
     list = (netdbEntry **)xcalloc(memInUse(MEM_NETDBENTRY), sizeof(netdbEntry *));
     i = 0;
     hash_first(addr_table);
 
-    while ((n = (netdbEntry *) hash_next(addr_table)))
-        *(list + i++) = n;
+    while ((n = (netdbEntry *) hash_next(addr_table))) {
+        *(list + i) = n;
+        ++i;
+    }
 
     if (i != memInUse(MEM_NETDBENTRY))
         debugs(38, 0, "WARNING: netdb_addrs count off, found " << i <<
                ", expected " << memInUse(MEM_NETDBENTRY));
 
     qsort((char *) list,
           i,
           sizeof(netdbEntry *),
           sortByRtt);
 
-    for (k = 0; k < i; k++) {
+    for (k = 0; k < i; ++k) {
         n = *(list + k);
         storeAppendPrintf(sentry, "%-46.46s %4d/%4d %7.1f %5.1f", /* Max between 16 (IPv4) or 46 (IPv6)   */
                           n->network,
                           n->pings_recv,
                           n->pings_sent,
                           n->rtt,
