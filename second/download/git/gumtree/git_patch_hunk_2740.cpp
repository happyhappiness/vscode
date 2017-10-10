 #define APPLE_LION_OR_NEWER
 #include <Security/Security.h>
 /* Apple's TYPE_BOOL conflicts with config.c */
 #undef TYPE_BOOL
 #endif
 
+#ifndef SHA1_MAX_BLOCK_SIZE
+#error Using Apple Common Crypto library requires setting SHA1_MAX_BLOCK_SIZE
+#endif
+
 #ifdef APPLE_LION_OR_NEWER
 #define git_CC_error_check(pattern, err) \
 	do { \
 		if (err) { \
 			die(pattern, (long)CFErrorGetCode(err)); \
 		} \
