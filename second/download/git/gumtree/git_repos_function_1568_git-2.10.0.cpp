static inline size_t st_add(size_t a, size_t b)
{
	if (unsigned_add_overflows(a, b))
		die("size_t overflow: %"PRIuMAX" + %"PRIuMAX,
		    (uintmax_t)a, (uintmax_t)b);
	return a + b;
}