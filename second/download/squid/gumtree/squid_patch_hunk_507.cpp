 
     assert(e);
     assert(e->e_info);
     addr = e->e_addr.addr;
     mask = e->e_mask.addr;
     storeAppendPrintf(sentry, "%s/%d\t",
-                      addr.NtoA(buf, MAX_IPSTRLEN),
-                      mask.GetCIDR() );
+                      addr.toStr(buf, MAX_IPSTRLEN),
+                      mask.cidr() );
     asinfo = e->e_info;
     assert(asinfo->as_number);
 
     for (q = asinfo->as_number; q; q = q->next)
         storeAppendPrintf(sentry, " %d", q->element);
 
