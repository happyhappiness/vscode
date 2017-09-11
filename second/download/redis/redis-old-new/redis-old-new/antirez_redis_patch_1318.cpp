@@ -346,7 +346,6 @@ static int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
     int16_t i16;
     int32_t i32;
     int64_t i64, ret = 0;
-    printf("%02x\n", encoding);
     if (encoding == ZIP_INT_8B) {
         ret = ((char*)p)[0];
     } else if (encoding == ZIP_INT_16B) {