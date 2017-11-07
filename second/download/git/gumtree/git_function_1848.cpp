static inline size_t st_sub(size_t a, size_t b)
{
	if (a < b)
		die("size_t underflow: %"PRIuMAX" - %"PRIuMAX,
		    (uintmax_t)a, (uintmax_t)b);
	return a - b;
}