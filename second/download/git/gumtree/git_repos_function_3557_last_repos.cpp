static void fit_variant(struct rerere_dir *rr_dir, int variant)
{
	variant++;
	ALLOC_GROW(rr_dir->status, variant, rr_dir->status_alloc);
	if (rr_dir->status_nr < variant) {
		memset(rr_dir->status + rr_dir->status_nr,
		       '\0', variant - rr_dir->status_nr);
		rr_dir->status_nr = variant;
	}
}