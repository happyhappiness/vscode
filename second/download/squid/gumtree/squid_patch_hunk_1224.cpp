  * Puts report on MemBuf _module_ usage into mb
  */
 void
 memBufReport(MemBuf * mb)
 {
     assert(mb);
-    mb->Printf("memBufReport is not yet implemented @?@\n");
+    mb->appendf("memBufReport is not yet implemented @?@\n");
 }
 
-#if !_USE_INLINE_
-#include "MemBuf.cci"
-#endif
-
