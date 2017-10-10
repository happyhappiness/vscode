	if (!ce)
		fprintf(o, "%s (missing)\n", label);
	else
		fprintf(o, "%s%06o %s %d\t%s\n",
			label,
			ce->ce_mode,
			sha1_to_hex(ce->sha1),
			ce_stage(ce),
			ce->name);
}
#endif

int threeway_merge(const struct cache_entry * const *stages,
