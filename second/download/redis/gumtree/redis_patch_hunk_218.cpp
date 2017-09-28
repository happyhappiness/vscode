  *
  * After the call, the modified sds string is no longer valid and all the
  * references must be substituted with the new pointer returned by the call.
  *
  * Example:
  *
- * s = sdsempty("Sum is: ");
+ * s = sdsnew("Sum is: ");
  * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
  *
  * Often you need to create a string from scratch with the printf-alike
  * format. When this is the need, just use sdsempty() as the target string:
  *
  * s = sdscatprintf(sdsempty(), "... your format ...", args);
