void maybe_log_item(struct file_struct *file, int iflags, int itemizing,
		    char *buf)
{
	int significant_flags = iflags & SIGNIFICANT_ITEM_FLAGS;
	int see_item = itemizing && (significant_flags || *buf || verbose > 1);
	int local_change = iflags & ITEM_LOCAL_CHANGE
	    && (!(iflags & ITEM_XNAME_FOLLOWS) || significant_flags);
	if (am_server) {
		if (am_daemon && !dry_run && see_item)
			log_item(file, &stats, iflags, buf);
	} else if (see_item || local_change || *buf
	    || (S_ISDIR(file->mode) && significant_flags))
		log_item(file, &stats, iflags, buf);
}