 	output[17] = (unsigned char)(ctx->ihv[4] >> 16);
 	output[18] = (unsigned char)(ctx->ihv[4] >> 8);
 	output[19] = (unsigned char)(ctx->ihv[4]);
 	return ctx->found_collision;
 }
 
-void git_SHA1DCFinal(unsigned char hash[20], SHA1_CTX *ctx)
-{
-	if (!SHA1DCFinal(hash, ctx))
-		return;
-	die("SHA-1 appears to be part of a collision attack: %s",
-	    sha1_to_hex(hash));
-}
-
-void git_SHA1DCUpdate(SHA1_CTX *ctx, const void *vdata, unsigned long len)
-{
-	const char *data = vdata;
-	/* We expect an unsigned long, but sha1dc only takes an int */
-	while (len > INT_MAX) {
-		SHA1DCUpdate(ctx, data, INT_MAX);
-		data += INT_MAX;
-		len -= INT_MAX;
-	}
-	SHA1DCUpdate(ctx, data, len);
-}
+#ifdef SHA1DC_CUSTOM_TRAILING_INCLUDE_SHA1_C
+#include SHA1DC_CUSTOM_TRAILING_INCLUDE_SHA1_C
+#endif
