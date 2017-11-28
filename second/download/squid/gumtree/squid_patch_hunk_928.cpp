 /* DEBUG: section 28    Access Control */
 
 #include "squid.h"
 #include "acl/Checklist.h"
 #include "acl/Ip.h"
 #include "cache_cf.h"
+#include "ConfigParser.h"
 #include "Debug.h"
 #include "ip/tools.h"
 #include "MemBuf.h"
 #include "wordlist.h"
 
 void *
-ACLIP::operator new (size_t byteCount)
+ACLIP::operator new (size_t)
 {
     fatal ("ACLIP::operator new: unused");
     return (void *)1;
 }
 
 void
-ACLIP::operator delete (void *address)
+ACLIP::operator delete (void *)
 {
     fatal ("ACLIP::operator delete: unused");
 }
 
 /**
  * print/format an acl_ip_data structure for debugging output.
