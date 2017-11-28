 free_acl_access(acl_access ** head)
 {
     aclDestroyAccessList(head);
 }
 
 static void
-dump_address(StoreEntry * entry, const char *name, IpAddress &addr)
+dump_address(StoreEntry * entry, const char *name, Ip::Address &addr)
 {
     char buf[MAX_IPSTRLEN];
     storeAppendPrintf(entry, "%s %s\n", name, addr.NtoA(buf,MAX_IPSTRLEN) );
 }
 
 static void
-parse_address(IpAddress *addr)
+parse_address(Ip::Address *addr)
 {
     char *token = strtok(NULL, w_space);
 
     if (!token) {
         self_destruct();
         return;
