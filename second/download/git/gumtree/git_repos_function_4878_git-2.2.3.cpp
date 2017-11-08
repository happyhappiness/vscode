static int debug_merge(const struct cache_entry * const *stages,
		       struct unpack_trees_options *o)
{
	int i;

	printf("* %d-way merge\n", o->merge_size);
	debug_stage("index", stages[0], o);
	for (i = 1; i <= o->merge_size; i++) {
		char buf[24];
		sprintf(buf, "ent#%d", i);
		debug_stage(buf, stages[i], o);
	}
	return 0;
}