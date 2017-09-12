@@ -2828,8 +2828,6 @@ static int rdbSaveLzfStringObject(FILE *fp, robj *obj) {
     outlen = sdslen(obj->ptr)-4;
     if (outlen <= 0) return 0;
     if ((out = zmalloc(outlen+1)) == NULL) return 0;
-    printf("Calling LZF with ptr: %p\n", (void*)obj->ptr);
-    fflush(stdout);
     comprlen = lzf_compress(obj->ptr, sdslen(obj->ptr), out, outlen);
     if (comprlen == 0) {
         zfree(out);