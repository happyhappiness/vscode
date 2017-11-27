static void za_submit_ratio (const char* type_instance, gauge_t hits, gauge_t misses)
{
	gauge_t ratio = NAN;

	if (!isfinite (hits) || (hits < 0.0))
		hits = 0.0;
	if (!isfinite (misses) || (misses < 0.0))
		misses = 0.0;

	if ((hits != 0.0) || (misses != 0.0))
		ratio = hits / (hits + misses);

	za_submit_gauge ("cache_ratio", type_instance, ratio);
}