 void SHA1DCUpdate(SHA1_CTX*, const char*, size_t);
 
 /* obtain SHA-1 hash from SHA-1 context */
 /* returns: 0 = no collision detected, otherwise = collision found => warn user for active attack */
 int  SHA1DCFinal(unsigned char[20], SHA1_CTX*);
 
-/*
- * Same as SHA1DCFinal, but convert collision attack case into a verbose die().
- */
-void git_SHA1DCFinal(unsigned char [20], SHA1_CTX *);
-
-/*
- * Same as SHA1DCUpdate, but adjust types to match git's usual interface.
- */
-void git_SHA1DCUpdate(SHA1_CTX *ctx, const void *data, unsigned long len);
-
-#define platform_SHA_CTX SHA1_CTX
-#define platform_SHA1_Init SHA1DCInit
-#define platform_SHA1_Update git_SHA1DCUpdate
-#define platform_SHA1_Final git_SHA1DCFinal
-
 #if defined(__cplusplus)
 }
 #endif
 
-#endif /* SHA1DC_SHA1_H */
+#ifdef SHA1DC_CUSTOM_TRAILING_INCLUDE_SHA1_H
+#include SHA1DC_CUSTOM_TRAILING_INCLUDE_SHA1_H
+#endif
+
+#endif
