     int i;
     int j;
     char buf[MAX_IPSTRLEN];
     storeAppendPrintf(sentry, "Internal DNS Statistics:\n");
     storeAppendPrintf(sentry, "\nThe Queue:\n");
     storeAppendPrintf(sentry, "                       DELAY SINCE\n");
-    storeAppendPrintf(sentry, "  ID   SIZE SENDS FIRST SEND LAST SEND\n");
-    storeAppendPrintf(sentry, "------ ---- ----- ---------- ---------\n");
+    storeAppendPrintf(sentry, "  ID   SIZE SENDS FIRST SEND LAST SEND M FQDN\n");
+    storeAppendPrintf(sentry, "------ ---- ----- ---------- --------- - ----\n");
 
     for (n = lru_list.head; n; n = n->next) {
         q = (idns_query *)n->data;
-        storeAppendPrintf(sentry, "%#06x %4d %5d %10.3f %9.3f\n",
+        storeAppendPrintf(sentry, "%#06x %4d %5d %10.3f %9.3f %c %s\n",
                           (int) q->query_id, (int) q->sz, q->nsends,
                           tvSubDsec(q->start_t, current_time),
-                          tvSubDsec(q->sent_t, current_time));
+                          tvSubDsec(q->sent_t, current_time),
+                          (q->permit_mdns? 'M':' '),
+                          q->name);
     }
 
     if (Config.dns.packet_max > 0)
-        storeAppendPrintf(sentry, "DNS jumbo-grams: %zd Bytes\n", Config.dns.packet_max);
+        storeAppendPrintf(sentry, "\nDNS jumbo-grams: %zd Bytes\n", Config.dns.packet_max);
     else
-        storeAppendPrintf(sentry, "DNS jumbo-grams: not working\n");
+        storeAppendPrintf(sentry, "\nDNS jumbo-grams: not working\n");
 
     storeAppendPrintf(sentry, "\nNameservers:\n");
-    storeAppendPrintf(sentry, "IP ADDRESS                                     # QUERIES # REPLIES\n");
-    storeAppendPrintf(sentry, "---------------------------------------------- --------- ---------\n");
+    storeAppendPrintf(sentry, "IP ADDRESS                                     # QUERIES # REPLIES Type\n");
+    storeAppendPrintf(sentry, "---------------------------------------------- --------- --------- --------\n");
 
     for (i = 0; i < nns; ++i) {
-        storeAppendPrintf(sentry, "%-45s %9d %9d\n",  /* Let's take the maximum: (15 IPv4/45 IPv6) */
-                          nameservers[i].S.NtoA(buf,MAX_IPSTRLEN),
+        storeAppendPrintf(sentry, "%-45s %9d %9d %s\n",  /* Let's take the maximum: (15 IPv4/45 IPv6) */
+                          nameservers[i].S.toStr(buf,MAX_IPSTRLEN),
                           nameservers[i].nqueries,
-                          nameservers[i].nreplies);
+                          nameservers[i].nreplies,
+                          nameservers[i].mDNSResolver?"multicast":"recurse");
     }
 
     storeAppendPrintf(sentry, "\nRcode Matrix:\n");
     storeAppendPrintf(sentry, "RCODE");
 
     for (i = 0; i < MAX_ATTEMPT; ++i)
