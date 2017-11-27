static int submit_cache_ratio (const char *host, /* {{{ */
		const char *plugin_inst,
		const char *type_inst,
		uint64_t new_hits,
		uint64_t new_misses,
		uint64_t old_hits,
		uint64_t old_misses,
		time_t timestamp,
		int interval)
{
	value_t v;

	if ((new_hits >= old_hits) && (new_misses >= old_misses)) {
		uint64_t hits;
		uint64_t misses;

		hits = new_hits - old_hits;
		misses = new_misses - old_misses;

		v.gauge = 100.0 * ((gauge_t) hits) / ((gauge_t) (hits + misses));
	} else {
		v.gauge = NAN;
	}

	return (submit_values (host, plugin_inst, "cache_ratio", type_inst,
				&v, 1, timestamp, interval));
}