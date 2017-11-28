         fatal ("Unknown acl type in ACL::Factory");
 
     return result;
 }
 
 ACL::ACL() :
+    cfgline(nullptr),
+    next(nullptr),
+    registered(false)
+{
+    *name = 0;
+}
+
+ACL::ACL(const ACLFlag flgs[]) :
     cfgline(NULL),
     next(NULL),
+    flags(flgs),
     registered(false)
 {
     *name = 0;
 }
 
 bool ACL::valid () const
