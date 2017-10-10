 	vreportf("warning: ", warn, params);
 }
 
 static int die_is_recursing_builtin(void)
 {
 	static int dying;
-	return dying++;
+	/*
+	 * Just an arbitrary number X where "a < x < b" where "a" is
+	 * "maximum number of pthreads we'll ever plausibly spawn" and
+	 * "b" is "something less than Inf", since the point is to
+	 * prevent infinite recursion.
+	 */
+	static const int recursion_limit = 1024;
+
+	dying++;
+	if (dying > recursion_limit) {
+		return 1;
+	} else if (dying == 2) {
+		warning("die() called many times. Recursion error or racy threaded death!");
+		return 0;
+	} else {
+		return 0;
+	}
 }
 
 /* If we are in a dlopen()ed .so write to a global variable would segfault
  * (ugh), so keep things static. */
 static NORETURN_PTR void (*usage_routine)(const char *err, va_list params) = usage_builtin;
 static NORETURN_PTR void (*die_routine)(const char *err, va_list params) = die_builtin;
