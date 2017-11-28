 /* DEBUG: section 28    Access Control */
 
 #include "squid.h"
 #include "acl/Checklist.h"
 #include "acl/TimeData.h"
 #include "cache_cf.h"
+#include "ConfigParser.h"
 #include "Debug.h"
 #include "wordlist.h"
 
 ACLTimeData::ACLTimeData () : weekbits (0), start (0), stop (0), next (NULL) {}
 
 ACLTimeData::ACLTimeData(ACLTimeData const &old) : weekbits(old.weekbits), start (old.start), stop (old.stop), next (NULL)
