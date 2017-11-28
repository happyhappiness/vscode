 int
 ACL::matchForCache(ACLChecklist *checklist)
 {
     /* This is a fatal to ensure that cacheMatchAcl calls are _only_
      * made for supported acl types */
     fatal("aclCacheMatchAcl: unknown or unexpected ACL type");
-    return 0;		/* NOTREACHED */
+    return 0;       /* NOTREACHED */
 }
 
 /*
  * we lookup an acl's cached results, and if we cannot find the acl being
  * checked we check it and cache the result. This function is a template
  * method to support caching of multiple acl types.
