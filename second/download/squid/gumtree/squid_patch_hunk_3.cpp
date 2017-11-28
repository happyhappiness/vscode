 #endif
 #if HAVE_STRINGS_H
 #include <strings.h>
 #endif
 
 #include "rfc1035.h"
+#include "rfc2671.h"
 
 #define RFC1035_MAXLABELSZ 63
 #define rfc1035_unpack_error 15
 
 #if 0
 #define RFC1035_UNPACK_DEBUG  fprintf(stderr, "unpack error at %s:%d\n", __FILE__,__LINE__)
 #else
 #define RFC1035_UNPACK_DEBUG  (void)0
 #endif
 
 
 
-int rfc1035_errno;
-const char *rfc1035_error_message;
-
 /*
  * rfc1035HeaderPack()
  *
  * Packs a rfc1035_header structure into a buffer.
  * Returns number of octets packed (should always be 12)
  */
