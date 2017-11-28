         storeAppendPrintf(sentry, "\n");
         return;
     }
 
     /** \par
      * Cached entries have IPs listed with a BNF of:   ip-address '-' ('OK'|'BAD') */
-    for (k = 0; k < count; k++) {
+    for (k = 0; k < count; ++k) {
         /* Display tidy-up: IPv6 are so big make the list vertical */
         if (k == 0)
             storeAppendPrintf(sentry, " %45.45s-%3s\n",
                               i->addrs.in_addrs[k].NtoA(buf,MAX_IPSTRLEN),
                               i->addrs.bad_mask[k] ? "BAD" : "OK ");
         else
