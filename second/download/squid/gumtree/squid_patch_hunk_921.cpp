     return false;
 }
 
 /* ACL result caching routines */
 
 int
-ACL::matchForCache(ACLChecklist *checklist)
+ACL::matchForCache(ACLChecklist *)
 {
     /* This is a fatal to ensure that cacheMatchAcl calls are _only_
      * made for supported acl types */
     fatal("aclCacheMatchAcl: unknown or unexpected ACL type");
     return 0;       /* NOTREACHED */
 }
