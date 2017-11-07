static void memory_limit_check(size_t size)
{
	static int limit = -1;
	if (limit == -1) {
		const char *env = getenv("GIT_ALLOC_LIMIT");
		limit = env ? atoi(env) * 1024 : 0;
	}
	if (limit && size > limit)
		die("attempting to allocate %"PRIuMAX" over limit %d",
		    (intmax_t)size, limit);
}