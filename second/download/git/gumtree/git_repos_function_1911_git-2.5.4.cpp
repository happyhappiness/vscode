static void invalidate_one_directory(struct untracked_cache *uc,
				     struct untracked_cache_dir *ucd)
{
	uc->dir_invalidated++;
	ucd->valid = 0;
	ucd->untracked_nr = 0;
}