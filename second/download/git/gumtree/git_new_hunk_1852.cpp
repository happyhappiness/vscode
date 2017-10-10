}

/* Per entry merge function */
static int process_entry(struct merge_options *o,
			 const char *path, struct stage_data *entry)
{
	int clean_merge = 1;
	int normalize = o->renormalize;
	unsigned o_mode = entry->stages[1].mode;
	unsigned a_mode = entry->stages[2].mode;
	unsigned b_mode = entry->stages[3].mode;
	unsigned char *o_sha = stage_sha(entry->stages[1].sha, o_mode);
