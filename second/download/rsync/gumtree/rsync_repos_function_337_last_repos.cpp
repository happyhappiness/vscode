void maybe_log_item(struct file_struct *file, int iflags, int itemizing,
		    const char *buf)
{
	int significant_flags = iflags & SIGNIFICANT_ITEM_FLAGS;
	int see_item = itemizing && (significant_flags || *buf
		|| stdout_format_has_i > 1 || (INFO_GTE(NAME, 2) && stdout_format_has_i));
	int local_change = iflags & ITEM_LOCAL_CHANGE && significant_flags;
	if (am_server) {
		if (logfile_name && !dry_run && see_item
		 && (significant_flags || logfile_format_has_i))
			log_item(FLOG, file, iflags, buf);
	} else if (see_item || local_change || *buf
	    || (S_ISDIR(file->mode) && significant_flags)) {
		enum logcode code = significant_flags || logfile_format_has_i ? FINFO : FCLIENT;
		log_item(code, file, iflags, buf);
	}
}