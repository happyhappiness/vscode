static void assign_variant(struct rerere_id *id)
{
	int variant;
	struct rerere_dir *rr_dir = id->collection;

	variant = id->variant;
	if (variant < 0) {
		for (variant = 0; variant < rr_dir->status_nr; variant++)
			if (!rr_dir->status[variant])
				break;
	}
	fit_variant(rr_dir, variant);
	id->variant = variant;
}