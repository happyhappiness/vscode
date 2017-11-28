 void MemBuf::terminate()
 {
     assert(size < capacity);
     *space() = '\0';
 }
 
-/* calls memBufVPrintf */
-void
-MemBuf::Printf(const char *fmt,...)
-{
-    va_list args;
-    va_start(args, fmt);
-    vPrintf(fmt, args);
-    va_end(args);
-}
-
 /**
- * vPrintf for other printf()'s to use; calls vsnprintf, extends buf if needed
+ * vappendf for other printf()'s to use; calls vsnprintf, extends buf if needed
  */
 void
-MemBuf::vPrintf(const char *fmt, va_list vargs)
+MemBuf::vappendf(const char *fmt, va_list vargs)
 {
 #ifdef VA_COPY
     va_list ap;
 #endif
 
     int sz = 0;
