 }
 
 void
 dump_externalAclHelper(StoreEntry * sentry, const char *name, const external_acl * list)
 {
     const external_acl *node;
-    const external_acl_format *format;
     const wordlist *word;
 
     for (node = list; node; node = node->next) {
         storeAppendPrintf(sentry, "%s %s", name, node->name);
 
         if (!node->local_addr.isIPv6())
