  *
  * -- "pack" (no need to handle offsets or check for overflows)
  * buf.Printf(...);
  * ...
  *
  * -- write
- * comm_write_mbuf(fd, buf, handler, data);
+ * Comm::Write(fd, buf, callback);
  *
  * -- *iff* you did not give the buffer away, free it yourself
  * -- buf.clean();
  * }
  \endverbatim
  */
 
 /* if you have configure you can use this */
 #if defined(HAVE_CONFIG_H)
-#include "config.h"
+#include "squid.h"
 #endif
 
 #ifdef VA_COPY
 #undef VA_COPY
 #endif
 #if defined HAVE_VA_COPY
 #define VA_COPY va_copy
 #elif defined HAVE___VA_COPY
 #define VA_COPY __va_copy
 #endif
 
-#include "squid.h"
+#include "squid-old.h"
 #include "MemBuf.h"
 
 /* local constants */
 
 /* default values for buffer sizes, used by memBufDefInit */
 #define MEM_BUF_INIT_SIZE   (2*1024)
