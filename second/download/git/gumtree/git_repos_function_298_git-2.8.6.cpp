static int ce_modified_check_fs(const struct cache_entry *ce, struct stat *st)
{
	switch (st->st_mode & S_IFMT) {
	case S_IFREG:
		if (ce_compare_data(ce, st))
			return DATA_CHANGED;
		break;
	case S_IFLNK:
		if (ce_compare_link(ce, xsize_t(st->st_size)))
			return DATA_CHANGED;
		break;
	case S_IFDIR:
		if (S_ISGITLINK(ce->ce_mode))
			return ce_compare_gitlink(ce) ? DATA_CHANGED : 0;
	default:
		return TYPE_CHANGED;
	}
	return 0;
}