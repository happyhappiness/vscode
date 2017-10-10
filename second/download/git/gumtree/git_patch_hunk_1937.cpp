 static void do_nothing(size_t size)
 {
 }
 
 static void (*try_to_free_routine)(size_t size) = do_nothing;
 
-static void memory_limit_check(size_t size)
+static int memory_limit_check(size_t size, int gentle)
 {
-	static int limit = -1;
-	if (limit == -1) {
-		const char *env = getenv("GIT_ALLOC_LIMIT");
-		limit = env ? atoi(env) * 1024 : 0;
-	}
-	if (limit && size > limit)
-		die("attempting to allocate %"PRIuMAX" over limit %d",
-		    (intmax_t)size, limit);
+	static size_t limit = 0;
+	if (!limit) {
+		limit = git_env_ulong("GIT_ALLOC_LIMIT", 0);
+		if (!limit)
+			limit = SIZE_MAX;
+	}
+	if (size > limit) {
+		if (gentle) {
+			error("attempting to allocate %"PRIuMAX" over limit %"PRIuMAX,
+			      (uintmax_t)size, (uintmax_t)limit);
+			return -1;
+		} else
+			die("attempting to allocate %"PRIuMAX" over limit %"PRIuMAX,
+			    (uintmax_t)size, (uintmax_t)limit);
+	}
+	return 0;
 }
 
 try_to_free_t set_try_to_free_routine(try_to_free_t routine)
 {
 	try_to_free_t old = try_to_free_routine;
 	if (!routine)
